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
        auxTableau = createAuxiliarPL(tableau)
        auxTableau = canonicBase(auxTableau)
        auxTableau, status = solvePL(auxTableau)
        
        nRows, nCols = auxTableau.shape
        certificado = auxTableau[0, 0:nRows - 1]

        if auxTableau[0, -1] < 0:
            certificado = auxTableau[0, 0:nRows - 1]
            print('inviavel')
            print(certificado)
        elif auxTableau[0, -1] > 0:
            print('ilimitada')
            tableau = createTableau(matrix, b, objectFunction)
            print(getX(auxTableau, len(objectFunction)))
            _, _, V = np.linalg.svd(matrix, full_matrices=True)
            certificado = V[-1]
            print(certificado)
        else:
            print('otima')
            print(certificado)

    else:
        tableau, status = solvePL(tableau)
        nRows, nCols = tableau.shape
        certificado = tableau[0, 0:nRows - 1]
        if status == 'ilimitada':
            print(status)
            # Valor X
            print(getX(tableau, len(objectFunction)))
            # Certificado de ilimitabilidade
            _, _, V = np.linalg.svd(matrix, full_matrices=True)
            certificado = V[-1]
            print(certificado)
        else:
            print('otima')
            # Valor Otimo
            print(tableau[0, -1])
            # Valor de x
            print(getX(tableau, len(objectFunction)))
            # Certificado de ótimo
            print(certificado)


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

def solvePL(tableau):
    nRows = (tableau.shape)[0]
    status = ''

    while(True):

        objectiveFunction = tableau[0, nRows-1:-1]
        indx = None

        # Encontra o pivo
        for i in range(len(objectiveFunction)):
            if objectiveFunction[i] < 0:
                indx = i
                break

        if indx == None:
            break

        tableau, status = tableauPivoting(tableau, nRows - 1 + indx)

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

    for i in range(1, nRows):
        tableau[0] -= tableau[i]

    return tableau

def getX(tableau, nVar):
    nRows, nCols = tableau.shape

    printTableau(tableau)

    objectiveFunction = tableau[0, nRows - 1: nRows+nVar-1]

    x = []

    for i in range(len(objectiveFunction)):
        if objectiveFunction[i] == 0:
            for j in range(1, nRows):
                if tableau[j, i + nRows - 1] == 1:
                    x.append(tableau[j, -1])
        else:
            x.append(0)

    return x

def printTableau(tableau):
    print(tabulate(tableau, tablefmt='fancy_grid', floatfmt=".2f"))
    # print(tableau)
main()