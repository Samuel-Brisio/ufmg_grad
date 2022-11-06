import numpy as np

def toInt(inputList) -> None:
    outputList = []
    for e in inputList:
        outputList.append(int(e))
    
    inputList = outputList


def read_input():
    dimension = list(input())
    objectFunction = list(input())

    toInt(dimension)
    toInt(objectFunction)

    b = []
    matrix = []

    for i in range(dimension[0]):
        row = list(input)
        toInt(row)
        b.append(row.pop())
        matrix.append[row]
    
    return matrix, b

print(read_input())