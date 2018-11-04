import matplotlib.pyplot as plt
import numpy as np
for i in  range(1,6):
    data1 = np.loadtxt("func"+str(i)+".txt")
    data2 = np.loadtxt("comptime"+str(i)+".txt")
    
    plt.title("Optimal point vs initial guess")
    plt.subplot(2,5,i)
    plt.plot(data1, 'ro')
    plt.ylabel("No of function evaluations")
    plt.xlabel("Initial guess")
    
    #plt.plot(data[:,0], data[:,2]-data[:,1])
    
    plt.title("Function Evaluations vs delta BPM")
    
    plt.subplot(2,5,5+i)
    plt.plot(data2, "-bo", label = "compute time")
    plt.ylabel("Compute time")
    plt.xlabel("initial guess")
    
    plt.title("Compute time vs initial guess")


plt.show()

plt.figure(2)

