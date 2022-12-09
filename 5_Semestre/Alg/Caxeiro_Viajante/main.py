import random
import numpy as np
from heapq import *
from scipy.spatial import distance
import time
import argparse

from branch_and_bound import *
from approxTSP import *
from christofides import *





def main():

    args = argumentsParsing()

    start = time.time()
    
    data = instance(exp=args.expoent, seed=args.seed)

    if args.algorithm == 'BaB':
        TS = TravellingSalesman_BAB(data, args.distance)
        TS.solve()
    elif args.algorithm == 'TAT':
        TAT = ApproxTSP(data, args.distance)
        TAT.solve() 
    elif args.algorithm == 'Chris':
        Chris = Christofides(data=data, distanceType=args.distance)
        Chris.solve()
        # Chris.draw()

    print(f'Duration: {time.time() - start} seconds')


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
        points = np.random.randint(0, 2**10, (size, 2))
        uniquePoints = len(np.unique(points, axis=0))

    return points

def argumentsParsing():
    # Inicialize the parser
    parser = argparse.ArgumentParser(
    # Program Name
    prog= 'main.py',
    description= 'Solve the TSP problem using 3 algorithms, studed inn the Algorithm 2 class',
    # End of help message
    epilog= 'Example: main.py -a TAT -d euclidian'
    )

    # Algorithm Argument
    parser.add_argument('-a', '--algorithm', choices= ['BaB', 'TAT', 'Chris'], required=True, help= '''
    Specify which algorithm will run | 
    Options: [
        BaB -> branch and Bound, 
        TAT -> Twice Around the Tree, 
        Chris -> Christofides
        ]
    ''')
    
    # Metric Argument
    parser.add_argument('-d', '--distance', choices= ['euclidian', 'manhattan'], required=True, help='Specify which metrics the algorithm will use') 

    # Number of Intance Argument
    parser.add_argument('-e', '--expoent', type= int, choices= [3, 4, 5, 6, 7, 8, 9, 10], required=True, help= 'Specify the number of intances | instances == 2**expoent')

    # Seed Argument: for experiment reproducibility
    # If value = 0, than the program will use a random seed
    parser.add_argument('-s', '--seed', type=int, default=0)

    return parser.parse_args()


if __name__ == "__main__":
    main()