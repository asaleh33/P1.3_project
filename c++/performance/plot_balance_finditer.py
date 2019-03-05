#!/usr/bin/env python3

import matplotlib.pyplot as plt
import sys

font = {'family' : 'normal',
        'weight' : 'bold',
        'size'   : 15}

if len(sys.argv) != 3:
    print("Usage:", sys.argv[0], "file1 file2") 
    sys.exit(1)

def get_params(inputfile, par1, par2):
    size = []
    runtime = []
    file = open(inputfile, "r")
    for line in file:	
        sep = line.strip().split()
        size.append(int(sep[par1]))
        runtime.append(float(sep[par2]))
    return size, runtime;

file1 = sys.argv[1]
file2 = sys.argv[2]

size_balance, time_balance =  get_params(file1, 0, 1)
size_iter, time_iter =  get_params(file2, 0, 2)


# get plot
plt.plot(size_balance, time_balance, linestyle='-', linewidth=1.5, color='#FF8C00', label = "Tree Balance()")
plt.plot(size_iter, time_iter, linestyle='-', linewidth=1.5, color='#FF0000', label = "Tree Find() using iterator")
plt.legend(loc="best", prop={'size':10}, frameon=False)
plt.grid()
plt.yscale('log')
plt.xlabel('# of nodes', fontsize=15)
plt.ylabel('Time [s]', fontsize=15)
plt.title(r"$Balance()\ &\ Find()\ using\ Iterator\ performances$", fontsize=14)
plt.rc('font', **font)
plt.tight_layout()
plt.savefig('balance_find_iter_perf.pdf')
#plt.show()
