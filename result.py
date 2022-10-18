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
        ysh.append(int(y) * 10**(-6))
    else:
        xsm.append(int(x))
        ysm.append(int(y) * 10**(-6))

fig = pyplot.figure()
axes = fig.subplots(2, 3)

axes[0][0].scatter(xsb, ysb, s=2)
axes[0][1].scatter(xsh, ysh, s=2)
axes[0][2].scatter(xsm, ysm, s=2)

ysb = [ysb[i] / xsb[i] / xsb[i] * 1000 for i in range(1, len(ysb))]
ysh = [ysh[i] / xsh[i] / np.log2(xsh[i]) * 1000 for i in range(1, len(ysh))]
ysm = [ysm[i] / xsm[i] / np.log2(xsm[i]) * 1000 for i in range(1, len(ysm))]

axes[1][0].scatter(xsb[1:], ysb, s=2)
axes[1][1].scatter(xsh[1:], ysh, s=2)
axes[1][2].scatter(xsm[1:], ysm, s=2)

axes[0][0].title.set_text("BubbleSort")
axes[0][0].set_ylabel("Time, msec")

axes[0][1].title.set_text("HeapSort")
axes[0][1].set_ylabel("Time, msec")

axes[0][2].title.set_text("MergeSort")
axes[0][2].set_ylabel("Time, msec")

axes[1][0].set_xlabel("Count")
axes[1][0].set_ylabel("Const(y / n^2)")

axes[1][1].set_xlabel("Count")
axes[1][1].set_ylabel("Const(y / (n * log2(n))")

axes[1][2].set_xlabel("Count")
axes[1][2].set_ylabel("Const(y / (n * log2(n))")

pyplot.show()



