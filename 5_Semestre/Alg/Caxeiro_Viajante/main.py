import random
import numpy as np
from heapq import *
from scipy.spatial import distance 
import time

from branch_and_bound import *

def main():
    start = time.time()
    
    data = instance(exp=4)
    # manhattanMatrix = distance2D(data, euclidian=False)
    # euclidianMatrix = distance2D(data, euclidian=True)

    TS = TravellingSalesman_BAB(data, 'manhattan')
    TS.solve()

    print(f'Duration: {time.time() - start} seconds')

    return "Em progresso"


def instance(exp=0, seed=0):

    if seed <= 0:
        seed = random.randint(1, 500)
    
    np.random.seed(seed)
    random.seed(seed)

    if not exp:
        exp = random.randint(4, 10)

    # if (exp < 4 or exp > 10):
    #     print("Error: points number")
    #     exit(15)
        
    size = 2**exp

    points = np.array(0)
    uniquePoints = 0

    while size != uniquePoints:
        points = np.random.randint(0, 2048, (size, 2))
        uniquePoints = len(np.unique(points, axis=0))

    return points

main()
