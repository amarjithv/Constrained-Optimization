import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt

mpl.rcParams['legend.fontsize'] = 10
for i in [1, 2, 5]:
    df = np.loadtxt("cg"+str(i)+".txt", delimiter = " ")
    x1 = df[:,0]
    y1 = df[:,1]
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    X = np.linspace(-10, 10, 1000)
    Y = np.linspace(-10, 10, 1000)
    np.random.shuffle(Y)
    np.random.shuffle(X)
    if i == 5:
        z1=0.26*(x1**2+y1**2)-0.48*x1*y1
        z=0.26*(X**2+Y**2)-0.48*X*Y
#z1=100*((y1)-(x1))**2 + ((x1)-1)**2
    elif i == 1:
        z1=x1**2+2*y1**2
        z=X**2+2*Y**2
    elif i ==2:
        z2=100*(y1-x1**2)**2+(x1-1)**2

    z=0.26*(X**2+Y**2)-0.48*X*Y
    #z = 100*((Y)-(X))**2 + ((X)-1)**2
    print(z.shape)
    ax.scatter(X, Y, z, label='parametric curve')
    ax.plot(x1 ,y1, z1, '-r')
    ax.scatter(x1, y1,  z1, '-y')
    ax.legend()
    
    plt.show()
