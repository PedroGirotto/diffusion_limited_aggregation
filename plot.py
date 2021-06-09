import numpy as np
import matplotlib.pyplot as plt

matriz = np.loadtxt("matriz.txt")

x = np.argwhere(matriz == 1)

for i in x:
    matriz[i[0], i[1]] = 0

plt.matshow(matriz)
plt.savefig("matriz.png")
plt.show()