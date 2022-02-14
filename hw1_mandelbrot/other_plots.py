#!/usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt

x = [.01, .005, .0025, .00125]
y = [1.518400, 1.535200, 1.536400, 1.542000]
d = [(y[i+1] - y[i]) / (x[i+1] - x[i]) for i in [0,1,2]]
print(d)
plt.plot(x,y)
plt.xlabel('resolution; reciprocal of number of grid points')
plt.ylabel('estimated area')
plt.savefig('area.png')

plt.clf()
def f(x):
    return 5e9 / (2*x + 100*(1-x))

x = np.linspace(0,1,100)
plt.plot(x, f(x))
plt.xlabel('f_c')
plt.ylabel('performance (FLOPS)')
plt.savefig('performance.png')
