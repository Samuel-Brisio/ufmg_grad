import random
import numpy as np
import time
import argparse
from threading import Timer
import os
import signal
from memory_profiler import profile

from classe import *


def over30min():
    print(f'Duração do Programa: NA seconds')
    print(f'Seed Used: NA')
    print(f'Uso da Memória: NA')
    os.kill(os.getpid(), signal.SIGTERM)

@profile()
def main():
    # 30 minutes timer
    timelimite = 60 * 30
    timer = Timer(timelimite, over30min)
    timer.start()

    args = argumentsParsing()

    start = time.time()
    print(f'Program Arguments: {args}')
    
    data, seed = instance(exp=args.expoent, seed=args.seed)

    if args.algorithm == 'BaB':
        TS = TravellingSalesman_BAB(data, args.distance)
        TS.solve()
    elif args.algorithm == 'TAT':
        TAT = TwiceAroundTreeTSP(data, args.distance)
        TAT.solve() 
    elif args.algorithm == 'Chris':
        Chris = Christofides(data=data, distanceType=args.distance)
        Chris.solve()

    timer.cancel()
    print(f'Duração do Programa: {time.time() - start} seconds')
    print(f'Seed Used: {seed}')
    print()
    print()

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

    return points, seed

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