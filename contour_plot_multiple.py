import matplotlib
import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
for i in range(1, 6):
    filename = "cg"+str(i)+".txt"
    Data = np.loadtxt(filename, delimiter = " ", usecols= [0,1])
    
    fig = plt.figure(figsize=plt.figaspect(0.5))
    
    
    delta = 0.25
    
    xn_lim = np.min(Data[:,0]) - 3
    xp_lim = np.max(Data[:,0]) + 3
    
    yn_lim = np.min(Data[:,1]) - 3
    yp_lim = np.max(Data[:,1]) + 3
    
    print(xn_lim)
    print(xp_lim)
    print(yn_lim)
    print(yp_lim)
    
    x = np.arange(xn_lim, xp_lim, delta)
    y = np.arange(yn_lim, yp_lim, delta)
    X, Y = np.meshgrid(x, y)
    if i==2{
        Z1 = 100*(Y-X**2)**2+ (X-1)**2
    
        Z2 = 100*(Data[:,1]-Data[:,0]**2)**2+ (Data[:,0]-1)**2
    }
    elif i==1{


    Z2 = Z2.reshape(-1,1)
    print(Z1)
    print(X)
    print(Y)
    
    ax = fig.add_subplot(1, 2, 1, projection='3d')
    ax.plot_surface( X = X, Y = Y, Z = Z1,cmap='viridis', edgecolor='none')
    ax.plot3D(np.ravel(Data[:,0]),np.ravel(Data[:,1]), np.ravel(Z2))
    ax.view_init(60, 35)
    fig = plt.gcf()
    fig.set_size_inches(10,7)
    #plt.savefig("3d.png")
    #plt.show()
    
    levels = np.arange(np.min(Z1), np.max(Z1),500)
    ax = fig.add_subplot(1, 2, 2)
    CS = ax.contour(X, Y, Z1, levels = levels)
    #ax.clabel(CS, inline=0, fontsize=10)
    ax.set_title('Simplest default with labels')
    x = Data[:,0].reshape(-1,1)
    y = Data[:,1].reshape(-1,1)
    plt.scatter(x,y)
    for i in range(len(x)-1):
        if (x[i+1,0] != x[i,0]) & (y[i+1,0] != y[i,0]) :
                plt.arrow(x[i+1,0],y[i+1,0],x[i,0]-x[i+1,0],y[i,0]-y[i+1,0], fc="b", ec="b",head_width=0.05, head_length=0.05,length_includes_head = True)
    
    fig = plt.gcf()
    fig.set_size_inches(14,9)
    plt.savefig("contour.png")
    
    plt.show() 
