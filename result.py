from matplotlib import pyplot
import numpy as np

with open("1.csv") as F:
    s = F.readline().split()
print(s)
xsb, ysb, xsh, ysh, xsm, ysm = [], [], [], [], [], []

for i in range(len(s)):
    y, x, typeSort = s[i].split(",")
    if typeSort == "b":
        xsb.append(int(x))
        ysb.append(int(y) * 10**(-6))
    elif typeSort == "h":
        xsh.append(int(x))
        ysh.append(int(y) * 10**(-6) / int(x) / np.log2(int(x)))
    else:
        xsm.append(int(x))
        ysm.append(int(y) * 10**(-6) / int(x) / np.log2(int(x)))

fig = pyplot.figure()
axes = fig.subplots(3, 1)

axes[0].scatter(xsb, ysb, s=2)
axes[1].scatter(xsh, ysh, s=2)
axes[2].scatter(xsm, ysm, s=2)
axes[0].title.set_text("BubbleSort")
axes[0].set_xlabel("Count")
axes[0].set_ylabel("Time, msec")
axes[1].title.set_text("HeapSort")
axes[1].set_xlabel("Count")
axes[1].set_ylabel("Time, msec")
axes[2].title.set_text("MergeSort")
axes[2].set_xlabel("Count")
axes[2].set_ylabel("Time, msec")
pyplot.show()



