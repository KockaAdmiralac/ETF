from matplotlib import pyplot as plt
import numpy as np

def f(x):
    if x < 1:
        return 0
    elif 1 <= x < 2:
        return 1/6
    elif 2 <= x < 3:
        return 11/36
    elif 3 <= x < 4:
        return 91/216
    else:
        return 1

x = np.linspace(-1, 5, 1000)
plt.plot(x, [f(xi) for xi in x])
# plt.show()
plt.savefig('VIS K1 2023 zadatak 4 grafik.svg')
