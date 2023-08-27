import sys
import re
import os

means = {}

filenames = os.listdir(sys.argv[1])
filenames.sort()

for filename in filenames:
    with open(sys.argv[1] + filename) as file:
        times = []
        for line in file:
            
            lista = re.split(' ', line)
            hasDuration = True if re.search("Duration:", lista[0]) else False
            hasSolution = (len(lista[0][:-2]) == 1 and lista[0][:-2].isdecimal)
            if hasDuration:
                time = float(lista[1])
                times.append(time)
            if hasSolution:
                print(lista)

        mean = sum(times) / len(times)
        filename = filename[7:-4]
        means[filename] = {'mean': mean}
        print(f'{filename} mean time: \t\t {mean:.4f}')


