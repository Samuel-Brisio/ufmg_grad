import numpy as np
import re
from tabulate import tabulate

np.set_printoptions(precision=2)

def main():
    # Processa o input
    matrix, b, objectFunction = read_input()

    # Passa a PL para FPI e cria o tableau
    tableau = createTableau(matrix, b, objectFunction)

    # Verifica se temos uma solução basica viavel
    doenstHavTrivialSolution = bool(sum(b < 0))

    if doenstHavTrivialSolution:
        # Solve auxiliar PL
        auxTableau = createAuxiliarPL(tableau.copy())
        auxTableau = canonicBase(auxTableau.copy())
        auxTableau, status = solvePL(auxTableau.copy(), dual=False)
        
        nRows, _ = auxTableau.shape
        certificado = auxTableau[0, 0:nRows - 1]

        if auxTableau[0, -1] < 0:
            certificado = auxTableau[0, 0:nRows - 1]
            print('inviavel')
            printArray(certificado)
            return


    #Resolve a PL
    tableau, status = solvePL(tableau)

    nRows, nCols = tableau.shape

    # Registro de Operações
    certificado = tableau[0, 0:nRows - 1]

    if status == 'ilimitada':
        print(status)
        # Valor X
        printArray(getX(tableau, len(objectFunction)))
        # Certificado de ilimitabilidade
        _, _, V = np.linalg.svd(matrix, full_matrices=True)
        certificado = V[-1]
        printArray(certificado)
    else:
        print('otima')
        # Valor Otimo
        print(f"{tableau[0, -1]:.7f}")
        # Valor de x
        x = getX(tableau, len(objectFunction))
        printArray(x)
        # Certificado de ótimo
        printArray(certificado)

    
def solvePL(tableau, dual=True):
    nRows = (tableau.shape)[0]
    status = ''

    while(True):
        if dual:
            printTableau(tableau)

        objectiveFunction = tableau[0, nRows-1:-1]
        indx = None

        # Encontra o pivo
        for i in range(len(objectiveFunction)):
            if objectiveFunction[i] < 0:
                indx = i
                break

        if indx == None:
            break

        isPlDual = False

        for i in range(1, len(tableau[:, -1])):
            if tableau[i, -1] < 0 and bool(sum(tableau[i, nRows-1:-1])):
                isPlDual = True
                break

        if isPlDual:
            tableau, status = dualPl(tableau)

        if isPlDual and dual:
            tableau, status = dualPl(tableau)

        else:
            tableau, status = tableauPivoting(tableau, nRows - 1 + indx)

        eps = 10**(-8)
        tableau[np.abs(tableau) < eps] = 0

        if status != 'normal':
            break

    return tableau, status


def tableauPivoting(tableau, indx):
    lista = []

    for i in range(1, (tableau.shape)[0]):
        num = tableau[i, indx]
        if num <= 0:
            continue
        lista.append((tableau[i, -1] / tableau[i, indx], i))

    # se não encontrar nenhuma linha para pivotear, isso quer dizer que A_k < 0
    if len(lista) == 0:
        return tableau, 'ilimitada'

    # Pega o menor pivo
    pivo = min(lista)[1]

    # Realiza o pivoteamento da linha escolhida
    tableau[pivo] /= tableau[pivo, indx]

    # Realiza o pivoteamento na matrix
    for i in range((tableau.shape)[0]):
        num = tableau[i, indx]
        
        if i == pivo:
            continue

        elif num == 0:
            continue

        coef =  - (tableau[i, indx] / tableau[pivo, indx])
        tableau[i] = tableau[i] + coef * tableau[pivo]

    return tableau, 'normal'

def createAuxiliarPL(tableau):
    nRows, nCols  = (tableau.shape)
    auxTableau = np.empty((nRows, nCols + nRows - 1))

    # Garante que o b > 0
    for i in range(1, nRows):
        if(tableau[i,-1] < 0):
            tableau[i] *= -1

    # Registro de Operações e a matriz da PL
    auxTableau[:, :nCols - 1] = tableau[:, :-1]
    
    # b
    auxTableau[:, -1] = tableau[:, -1]
    
    # extendendo a matrix da PL
    auxTableau[1:, nCols-1:-1] = np.identity(nRows - 1)

    # função objetiva
    auxTableau[0] = np.zeros(nCols+nRows-1)
    auxTableau[0, nCols-1:-1] = np.ones(nRows - 1)

    return auxTableau

def canonicBase(tableau):
    nRows, nCols = tableau.shape
    nVars = nRows - 1

    for j in range(nVars, nCols-1):
        if tableau[0, j] != 0:
            for i in range(1, nRows):
                if tableau[i, j] == 1:
                    tableau[0] -= tableau[0, j] * tableau[i] 

    return tableau

def originalPL(tableau, auxTableau):
    nRows, _ = auxTableau.shape
    nRestriction = nRows - 1

    tableau[1:, nRestriction:-1] = auxTableau[1:, nRestriction: -(nRestriction+1)]
    tableau[:, -1] = auxTableau[:, -1]
    tableau[1:, nRestriction: 2*nRestriction] = np.identity(nRestriction)

    return tableau


def dualPl(tableau):
    nRows, nCols = tableau.shape

    hasNegativeB = bool(sum(tableau[1:, -1] < 0))
    lista = []
    row = 0

    for row in range(1, nRows):
        if tableau[row, -1] < 0:
            for j in range(nRows-1, nCols-1):
                if tableau[row, j] >= 0:
                    continue

                lista.append((tableau[0, j] / (-tableau[row, j]), (row, j)))

            tableau[row] *= -1
            break
                   
    # se não encontrar nenhuma Col_j para pivotear, isso quer dizer que Row_i todoas os elementos >= 0
    if len(lista) == 0:
        return tableau, "Não foi possivel executar o dual"

    # Pega o menor pivo
    pRow, pCol = min(lista)[1]

    # Realiza o pivoteamento da linha escolhida
    tableau[pRow] /= tableau[pRow, pCol]

    # Realiza o pivoteamento na matrix
    for i in range(nRows):
        num = tableau[i, pCol]
        
        if i == pRow:
            continue

        elif num == 0:
            continue

        coef =  - (tableau[i, pCol] / tableau[pRow, pCol])
        tableau[i] = tableau[i] + coef * tableau[pRow]

    return tableau, "normal"


def getX(tableau, nVar):
    nRows, nCols = tableau.shape
    objectiveFunction = tableau[0, nRows - 1: nRows+nVar-1]
    x = []

    for i in range(len(objectiveFunction)):
        if objectiveFunction[i] == 0 and bool(sum(tableau[:, i + nRows - 1] == 1)):
            for j in range(1, nRows):
                if tableau[j, i + nRows - 1] == 1:
                    x.append(tableau[j, -1])
        else:
            x.append(0)
    return x

def printTableau(tableau):
    # print(tabulate(tableau, tablefmt='fancy_grid', floatfmt=".2f"))
    # print(200 * '-')

    pass

def printArray(arr): 
    for i in range(len(arr)):
        print(f"{arr[i]:.7f}", end=" ")
    print()


def splitInput():
    string = input()
    lista = re.split(' ', string)

    npArray = np.asarray(lista)
    npArray = npArray.astype(int)

    return npArray

def read_input():
    
    dimension = splitInput()
    objectFunction = splitInput()

    b = np.empty(dimension[0])
    matrix = np.empty((dimension))

    for i in range(dimension[0]):
        row = splitInput()
        b[i] = row[-1]
        row = np.delete(row, -1)
        matrix[i] = row
    
    return matrix, b, objectFunction

def createTableau(matrix, b, objectiveFunction):
    nRows = b.size + 1
    nCols = (matrix.shape)[1] + 2 * b.size + 1
    tableau = np.empty((nRows, nCols))    

    # Registro de operações
    tableau[0, 0:b.size] = np.zeros(b.size)
    tableau[1:, 0:b.size] = np.identity(b.size)

    # Função objetiva
    tableau[0, b.size:(matrix.shape)[1]+ b.size] = (- objectiveFunction)
    tableau[0, (matrix.shape)[1]+ b.size: (matrix.shape)[1]+ 2*b.size] = np.zeros(b.size)

    #valor otimo
    tableau[0, -1] = 0.0

    #matrix
    tableau[1:, b.size:(matrix.shape)[1]+ b.size] = matrix
    tableau[1:, (matrix.shape)[1]+ b.size: (matrix.shape)[1]+ 2*b.size] = np.identity(b.size)

    #b
    tableau[1:, -1] = b

    return tableau

main()