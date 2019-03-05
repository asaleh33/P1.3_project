#!/usr/bin/env python3

import matplotlib.pyplot as plt
import sys

font = {'family' : 'normal',
        'weight' : 'bold',
        'size'   : 15}

if len(sys.argv) != 4:
    print("Usage:", sys.argv[0], "file1 file2 file3") 
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

for f1,f2, f3 in zip(sys.argv[1:], sys.argv[2:], sys.argv[3:]):
    size_unbalanced, time_unbalanced =  get_params(f1, 0, 2)
    size_balanced, time_balanced =  get_params(f2, 0, 2)
    size_stdmap, time_stdmap = get_params(f3, 0, 2) 
    print("\n", f1,"\n",f2,"\n",f3, "\n")


# get plot
plt.plot(size_unbalanced, time_unbalanced, linestyle='-', linewidth=1.5, color='#FF0000', label = "Tree unbalanced")
plt.plot(size_balanced, time_balanced, linestyle='-', linewidth=1.5, color='#FF8C00', label = "Tree balanced")
plt.plot(size_stdmap, time_stdmap, linestyle='-', linewidth=1.5, color='#90EE90', label =  "std::map")
plt.legend(loc="best", prop={'size':10}, frameon=False)
plt.grid()
plt.yscale('log')
plt.xlabel('# of nodes', fontsize=15)
plt.ylabel('Time [s]', fontsize=15)
plt.title(r"$Find ()\ performance$", fontsize=14)
plt.rc('font', **font)
plt.tight_layout()
plt.savefig('find_perf.pdf')
#plt.show()
