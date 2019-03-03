#!/usr/bin/env python3

import matplotlib.pyplot as plt
import sys

font = {'family' : 'normal',
        'weight' : 'bold',
        'size'   : 15}

if len(sys.argv) != 2:
    print("Usage:", sys.argv[0], "file1") 
    sys.exit(0)

def get_params(inputfile, par1, par2):
    size = []
    runtime = []
    file = open(inputfile, "r")
    for line in file:	
        sep = line.strip().split()
        size.append(int(sep[par1]))
        runtime.append(float(sep[par2]))
    return size, runtime;

#f1 = str(sys.argv[1])
inputfile = sys.argv[1]

size_balance, time_balance =  get_params(inputfile, 0, 1)


# get plot
plt.plot(size_balance, time_balance, linestyle='-', linewidth=1.5, color='#FF0000', label = "Tree Balance()")
#plt.plot(size_balanced, time_balanced, linestyle='-', linewidth=1.5, color='#FF8C00', label = "Tree balanced")
#plt.plot(size_stdmap, time_stdmap, linestyle='-', linewidth=1.5, color='#90EE90', label =  "std::map")
plt.legend(loc="best", prop={'size':10}, frameon=False)
plt.grid()
plt.yscale('log')
#plt.xlim(1,500000)
#plt.xticks([8,16,24,32,40])
##plt.yticks([1e3,1e4, 5e4]) # procs 8
#plt.yticks([1e3,1e4, 8e4]) # procs 48
plt.xlabel('# of nodes', fontsize=15)
plt.ylabel('Time [s]', fontsize=15)
plt.title(r"$Balance ()\ performance$", fontsize=15)
plt.rc('font', **font)
plt.tight_layout()
plt.savefig('balance_perf.pdf')
#plt.show()
