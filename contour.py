import matplotlib
import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt


delta = 0.025
x = np.arange(-10.0, 10.0, delta)
y = np.arange(-10.0, 10.0, delta)
X, Y = np.meshgrid(x, y)
Z1 = (X)**2 + 2*(Y)**2
#Z2 = ((X-1)-1.5)**2 + ((Y-1)-4)**2
#Z = (Z1 - Z2) * 2
print(Z1)
print(X)
print(Y)

levels = np.arange(0,300,10)
fig, ax = plt.subplots()
CS = ax.contour(X, Y, Z1, levels = levels)
ax.clabel(CS, inline=1, fontsize=10)
ax.set_title('Simplest default with labels')

fig = plt.gcf()
fig.set_size_inches(10,7)
plt.savefig("contour.png")

plt.show()

from mpl_toolkits.mplot3d import Axes3D
fig = plt.figure()
fig = plt.figure()
ax = fig.gca(projection='3d')
#ax = fig.add_subplot(111, projection='3d')
ax.plot(X, Y, Z1)
plt.show()
