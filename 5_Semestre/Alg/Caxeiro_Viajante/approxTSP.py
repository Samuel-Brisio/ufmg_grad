from scipy.spatial import distance
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

class ApproxTSP():
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
            
        self.G = self.__createGraph__()

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

    def __createGraph__(self):
        return nx.from_numpy_matrix(self.distanceMatrix)

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
        print(cost)
        nx.draw_networkx(self.G)
        plt.show()
        