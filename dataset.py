import numpy as np 
import matplotlib.pyplot as plt 
import random
import math
import pandas as pd

def gen_circle(sample_size, radius, cx=0, cy=0):
    r = np.random.uniform(0, 1, size=sample_size)
    angle = np.random.uniform(0, 1, size=sample_size)
    
    x = cx + radius * np.sqrt(r) * np.cos(2 * np.pi * angle)
    y = cy + radius * np.sqrt(r) * np.sin(2 * np.pi * angle)

    return x, y

N = 2500

# cluster details
radii = [3, 2, 5, 4, 6]
color_options = ['red', 'blue', 'green', 'orange', 'yellow']
centers = [(0, 10), (-24, 25), (10, -11), (-17, 1), (19, 2), (-34, 8)]
clusters = 5

X = []
Y = []
colors = []
cluster = []

plt.figure(figsize=(7,7))

for i in range(clusters):
    cx, cy = centers[i]
    x, y = gen_circle(N, radii[i], cx, cy)
    X.append(x)
    Y.append(y)
    colors.extend([color_options[i]] * N)
    cluster.extend([i] * N)

X = np.concatenate(X)
Y = np.concatenate(Y)

df = pd.DataFrame({
    'X': X,
    'Y': Y,
    'Cluster': cluster
})

df.to_csv('dataset.csv', sep = ' ', index = False)

plt.scatter(X, Y, c=colors)
plt.xlim(-40, 40)
plt.ylim(-40, 40)

plt.show()