import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("newton_raphson5.txt");
print(data)
plt.plot(data,'ro', label="x1");
#plt.plot(data[1:,1],'bo');
#plt.plot(data[1:,2],'-g');
plt.xlabel("iteration no");
plt.ylabel("Bound value");
plt.legend(("x1"));
plt.show();
