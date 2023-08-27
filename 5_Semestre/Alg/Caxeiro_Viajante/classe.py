from scipy.spatial import distance
import numpy as np
import networkx as nx
from heapq import *
import math



class TSP():
    def __init__(self, data, distanceType):
        # Set of Points
        self.data = data
        self.numInstance = (data.shape)[0]
        self.distanceMatrix = None
        self.__distance2D__(distanceType)    
        self.G = nx.from_numpy_matrix(self.distanceMatrix)

    def __distance2D__(self, metric):
        if metric == 'euclidian':
            funcDistance = distance.euclidean
        elif metric == 'manhattan':
            funcDistance = distance.cityblock
        
        size = self.numInstance
        self.distanceMatrix = np.empty((size, size))

        for i in range(size):
            for j in range(size):
                if i == j:
                    self.distanceMatrix[i][i] = 0    
                else:
                    self.distanceMatrix[i][j] = funcDistance(self.data[i], self.data[j])


class TwiceAroundTreeTSP (TSP):

    def solve(self):
        root = 0
        MST = nx.minimum_spanning_tree(self.G, algorithm='prim')
        hamiltonianCycle = nx.dfs_preorder_nodes(MST, root)
        hamiltonianNodes = list(hamiltonianCycle)

        cost = 0
        for i in range(len(hamiltonianNodes) -1):
            cost += self.distanceMatrix[hamiltonianNodes[i], hamiltonianNodes[i+1]]
        # close the cycle
        cost += self.distanceMatrix[-1, 0]
        print(f'Solução Ótima: {cost}')

class Christofides (TSP):
    
    def solve(self):
        root = 0
        MST = nx.minimum_spanning_tree(self.G, algorithm='prim')

        nodesWithOddDegree = []

        for i in range(self.numInstance):
            if MST.degree[i] % 2 != 0:
                nodesWithOddDegree.append(i)
        
        subGraph = self.G.subgraph(nodesWithOddDegree)
        
        # perfect matching
        M = nx.min_weight_matching(subGraph)

        # Transfor MST in multiGraph
        G_line = nx.MultiGraph(MST)
        
        # Add on G_line the edges from the perfect matching
        for edge in M:
            node_a = edge[0]
            node_b = edge[1]
            G_line.add_edge(node_a, node_b, weight = self.distanceMatrix[node_a, node_b])

        
        eulerianPath = nx.eulerian_path(G_line, root)
        eulerianPath = list(eulerianPath)

        # Get the nodes firt nodes from eulerianPath edges
        eulerianNodes = [edge[0] for edge in eulerianPath]
        eulerianNodes.append(0)

        nodes = set()
        lastNode = 0

        # Remove repetead nodes
        for i in range(len(eulerianNodes) - 1):
            node = eulerianNodes[i]
            if node in nodes:
                nextNode = eulerianNodes[i+1]                
                G_line.remove_edge(lastNode, node)
                G_line.remove_edge(node, nextNode)

                G_line.add_edge(lastNode, nextNode, weight= self.distanceMatrix[lastNode, nextNode])
            else:
                nodes.add(node)
                lastNode = node

        # Get the nodes in preorder
        hamiltonianNodes = nx.dfs_preorder_nodes(G_line, root)
        hamiltonianNodes = list(hamiltonianNodes)
        
        # Calculated the cost
        cost = 0
        for i in range(len(hamiltonianNodes) -1):
            cost += self.distanceMatrix[hamiltonianNodes[i], hamiltonianNodes[i+1]]
        # close the cycle
        cost += self.distanceMatrix[-1, 0]
        print(f'Solução Ótima: {cost}')


class Node:
    def __init__(self, bound, level, cost, solution):
        self.bound = bound
        self.cost = cost
        self.level = level
        self.sol = solution

    def __lt__(self, other):
        return self.bound < other.bound

    def __repr__(self) -> str:
        return f"estimativa: {self.bound}, custo atual: {self.cost}, nivel do nó: {self.level}, nós das soluções: {self.sol}"

    def __str__(self) -> str:
        return f"estimativa: {self.bound}, custo atual: {self.cost}, nivel do nó: {self.level}, nós das soluções: {self.sol}"
        

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

        self.best = np.inf
        self.solution = [] # Tem que ser uma lista pois o nó 0 se repete


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
                    setSolution = set(node.sol)
                    for k in range (1, self.size):
                        if (
                            k not in setSolution
                            and self.distanceMatrix[node.sol[-1], k] != np.inf
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
                    self.distanceMatrix[node.sol[-1], 0] != np.inf
                    and self.bound(node.sol + [0]) < self.best
                ):
                    newNode = Node(
                        self.bound(node.sol + [0]),
                        node.level + 1,
                        node.cost + self.distanceMatrix[node.sol[-1], 0],
                        node.sol + [0]
                    )

                    heappush(queue, newNode)

        print(f'Solução Ótima: {self.best}')