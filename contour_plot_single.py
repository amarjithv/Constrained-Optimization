import matplotlib
import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

filename = "cg2.txt"
Data = np.loadtxt(filename, delimiter = " ", usecols= [0,1])


fig = plt.figure()
ax = plt.axes(projection='3d')

delta = 0.025
x = np.arange(-5.0, 10.0, delta)
y = np.arange(-5.0, 10.0, delta)
X, Y = np.meshgrid(x, y)
Z1 = 100*(Y-X**2)**2+ (X-1)**2

Z2 = 100*(Data[:,1]-Data[:,0]**2)**2+ (Data[:,0]-1)**2
Z2 = Z2.reshape(-1,1)
print(Z1)
print(X)
print(Y)

ax.plot_surface( X = X, Y = Y, Z = Z1,cmap='viridis', edgecolor='none')
ax.scatter3D(Data[:,0],Data[:,1], Z2, cmap='black')
ax.view_init(60, 35)
fig = plt.gcf()
fig.set_size_inches(10,7)
plt.savefig("3d.png")
plt.show()

levels = np.arange(np.min(Z2), np.max(Z2),1)
fig, ax = plt.subplots()
CS = ax.contour(X, Y, Z1, levels = levels)
ax.clabel(CS, inline=1, fontsize=10)
ax.set_title('Simplest default with labels')
x = Data[:,0].reshape(-1,1)
y = Data[:,1].reshape(-1,1)
plt.scatter(x,y)
for i in range(len(x)-1):
    if (x[i+1,0] != x[i,0]) & (y[i+1,0] != y[i,0]) :
            plt.arrow(x[i+1,0],y[i+1,0],x[i,0]-x[i+1,0],y[i,0]-y[i+1,0], fc="b", ec="b",head_width=0.1, head_length=0.5,length_includes_head = True)

fig = plt.gcf()
fig.set_size_inches(10,7)
plt.savefig("contour.png")

plt.show() 
