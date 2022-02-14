#!/usr/bin/python3

import os
import numpy as np
import matplotlib.pyplot as plt

files = os.listdir('.')
for file in files:
    if file.endswith('.dat'):
        data = np.loadtxt(file)
        plt.clf()
        plt.scatter(data[:,0], data[:,1], s=.15)
        plt.xlabel('x')
        plt.ylabel('y')
        plt.savefig(file + '.png')
