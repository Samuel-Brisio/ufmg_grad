import numpy as np
import re

def main():
    # Processa o input
    matrix, b, objectFunction = read_input()

    # Passa a PL para FPI e cria o tableau
    tableau = createTableau(matrix, b, objectFunction)


    # Verifica se temos uma solução basica viavel
    doenstHavTrivialSolution = bool(sum(b < 0))

    if doenstHavTrivialSolution:
        # Solve auxiliar PL
        print("Esta parte ainda falta ser implementada")
        exit(42)

    solvePL(tableau)

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
    functionIdx = (nRows, (tableau.shape)[1] - 1)
    print(tableau)

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

        tableau = tableauPivoting(tableau, nRows - 1 + indx)
        print(50 * '-')
        print(tableau)


    


def tableauPivoting(tableau, indx):
    lista = []

    for i in range(1, (tableau.shape)[0]):
        num = tableau[i, indx]
        if num <= 0:
            continue
        lista.append((tableau[i, -1] / tableau[i, indx], i))

    if len(lista) == 0:
        print('tableau pivoting error, possivelmente esta pl é ilimitada')
        exit(42)

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

    return tableau

main()