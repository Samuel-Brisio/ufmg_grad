from heapq import *
from scipy.spatial import distance
import numpy as np
import math

class Node:
    def __init__(self, bound, level, cost, solution):
        self.bound = bound
        self.cost = cost
        self.level = level
        self.sol = solution

    def __lt__(self, other):
        return self.bound < other.bound
        

class TravellingSalesman_BAB:
    def __init__(self, data, distanceType):
        # Set of Points
        self.data = data
        self.size = (data.shape)[0]
        self.boundIndx = np.empty((self.size, 2))
        self.boundValue = np.empty_like(self.boundIndx)

        if distanceType == "euclidian":
            self.distanceMatrix = self.__distance2D__(euclidian=True)
        else:
            self.distanceMatrix = self.__distance2D__(euclidian=False)

        self.solution = None
        self.best = None

    # Ineficiente demora 4 segundo na distancia manhattan
    # E 6 segundos na distancia euclidiana no pior caso
    def __distance2D__(self, euclidian):
        if euclidian == True:
            funcDistance = distance.euclidean
        else:
            funcDistance = distance.cityblock
        
        size = len(self.data)
        distanceMatrix = np.empty((size, size))

        for i in range(size):
            for j in range(size):
                if i == j:
                    distanceMatrix[i][i] = np.inf    
                else:
                    distanceMatrix[i][j] = funcDistance(self.data[i], self.data[j])

        return distanceMatrix


    def __bound__(self, setSolution):
        sol = setSolution

        # Retorno os dois menores elementos de cada linha
        indice = np.argpartition(self.distanceMatrix, kth=2, axis=-1)
        self.boundIndx = indice[:, :2]
        self.boundValue = np.take_along_axis(self.distanceMatrix, indice, axis=1)[:, :2]

        # Só foi inserido um elemento até o momento
        # E portanto ainda não temos nenhuma aresta para fixar
        if len(sol) == 1:
            pass

        else:
            for i in range(len(sol) - 1):
                # bound[0] é uma lista no qual o primeiro elemento determina a entrada
                # e o segundo a saida
                distancia = self.distanceMatrix[sol[i]][sol[i+1]]
                
                # saida do vertice sol[i] é o vertice sol[i+1]
                self.boundIndx[sol[i], 1] = sol[i+1] 
                # A entrada do vertice sol[i+1] é o vertice sol[i]
                self.boundIndx[sol[i+1], 0] = sol[i]

                self.boundValue[sol[i], 1] = distancia
                self.boundValue[sol[i+1], 0] = distancia

    def bound(self, sol):
        self.boundIndx = None
        self.boundValue = None

        self.__bound__(sol)
        return self.getBound()


    def getBound(self):
        return math.ceil(np.sum(self.boundValue) / 2) 

    def solve(self):
        root = Node(self.bound([0]), 0, 0, [0])
        
        # Fila de prioridade com os nós que serão processados
        queue = [root]
        heapify(queue)

        self.best = np.infty
        self.solution = [] # Tem que ser uma lista pois o nó 0 se repete

        print(len(queue), "Ok")

        while len(queue) != 0:
            # Retira o nó com a menor estimativa
            node = heappop(queue)

            # Se já percorreu toda a arvore
            # E tiver um custo menor que o melhor
            if node.level > self.size-1 and self.best > node.cost:
                    self.best = node.cost
                    self.solution = node.sol

            elif node.bound < self.best:
                if node.level < self.size - 1:
                    for k in range (1, self.size-1):
                        if (
                            k not in set(node.sol)
                            and self.distanceMatrix[node.sol[-1], k] != np.infty
                            # Qual é a estimativa se o k entrar na solução 
                            and self.bound(node.sol + [k]) < self.best
                        ):

                            newNode = Node( 
                                self.bound(node.sol + [k]), 
                                node.level + 1,
                                node.cost + self.distanceMatrix[node.sol[-1], k],
                                node.sol + [k]
                                )

                            heappush(queue, newNode)

                # node.level == self.size - 1 
                # calcula se a volta para o nó inicial
                elif (
                    self.distanceMatrix[node.sol[-1][0]] != np.infty
                    and self.bound(node.sol + [0]) < self.best
                ):
                    newNode = Node(
                        self.bound(node.sol + [0]),
                        node.level + 1,
                        node.cost + self.distanceMatrix[node.s[-1], 0],
                        node.sol + [0]
                    )

                    heappush(queue, newNode)
