import numpy as np
import matplotlib.pyplot as plt

regiao = np.loadtxt("regiao.txt")

fig, ax = plt.subplots()
ax.matshow(regiao, cmap = "inferno")

plt.savefig("tree.png", dpi = 600)