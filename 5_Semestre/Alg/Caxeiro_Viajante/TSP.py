from scipy.spatial import distance
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

class TSP():
    def __init__(self, data, distanceType):
        # Set of Points
        self.data = data
        self.numInstance = (data.shape)[0]
        self.distanceMatrix = self.__distance2D__(distanceType)    
        self.G = nx.from_numpy_matrix(self.distanceMatrix)

    def __distance2D__(self, metric):
        if metric == 'euclidian':
            funcDistance = distance.euclidean
        elif metric == 'manhattan':
            funcDistance = distance.cityblock
        
        size = self.numInstance
        distanceMatrix = np.empty((size, size))

        for i in range(size):
            for j in range(size):
                if i == j:
                    distanceMatrix[i][i] = 0    
                else:
                    distanceMatrix[i][j] = funcDistance(self.data[i], self.data[j])

        return distanceMatrix
