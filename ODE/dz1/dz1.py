from matplotlib import pyplot as plt
import matplotlib
import numpy as np

T = 50
T_D = 10

def vb1(t):
    if t < 0:
        return 3.33
    return 4 - 0.66 * np.exp(-t/90)
def va1(t):
    if t < 0:
        return 6.66
    return 6 - 0.44 * np.exp(-t/90)
def vb2(t):
    if t < 0:
        return 4
    return 3.33 + 0.66 * np.exp(-t/100)
def va2(t):
    if t < 0:
        return 6
    return 6.66 + 0.34 * np.exp(-t/100)
def viop(t):
    if t % T >= 0 and t % T <= T_D:
        return 3 - 8 / 10 * (t % T)
    return -5 + 2 / 10 * (t % T - 10)
def vk(t):
    if t % T == T_D:
        return 0
    return 5

plt.figure()
plt.subplot(1, 2, 1)
plt.title('$v_a(t)$')
t = np.linspace(-100, 90 * 3, 1000)
plt.plot(t, [va1(x) for x in t])
plt.subplot(1, 2, 2)
plt.title('$v_b(t)$')
plt.plot(t, [vb1(x) for x in t])
plt.savefig('DZ1-1a.pgf')

plt.figure()
plt.subplot(1, 2, 1)
plt.title('$v_a(t)$')
t = np.linspace(-90, 100 * 3, 1000)
plt.plot(t, [va2(x) for x in t])
plt.subplot(1, 2, 2)
plt.title('$v_b(t)$')
plt.plot(t, [vb2(x) for x in t])
plt.savefig('DZ1-1b.pgf')

plt.figure()
plt.title('$V_{IOP}(t)$')
t = np.arange(100, 300, 1)
plt.plot(t, [viop(x) for x in t])
plt.title('$V_K(t)$')
plt.plot(t, [vk(x) for x in t])
plt.savefig('DZ1-2.pgf')

plt.show()
