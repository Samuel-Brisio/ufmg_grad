from scipy.spatial import distance
import numpy as np

class ApproxTST():
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

    def solve():
        root = "0"
        minTree = prim()
        H = "Preorder walk from the root"