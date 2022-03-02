from matplotlib import pyplot as plt
import numpy as np

def zad2_mua(x):
    if -4 <= x <= 0:
        return 1 + x/4
    if 0 < x <= 4:
        return 1 - x/4
    raise RuntimeError

def zad2_mub(x):
    if -4 <= x < -2:
        return 2 + x/2
    if -2 <= x < 0:
        return 1
    if 0 <= x < 2:
        return 1 - x/2
    if 2 <= x <= 4:
        return 0
    raise RuntimeError

def zad2_muc(x):
    if -1 <= x < 0:
        return x + 1
    if 0 <= x <= 1:
        return 1
    if 1 < x <= 3:
        return (3-x)/2
    raise RuntimeError

def zad2_union(x):
    return max(zad2_mua(x), zad2_mub(x))

def zad2_complb(x):
    return 1 - zad2_mub(x)

def zad2_complc(x):
    return 1 - zad2_muc(x)

def zad2_scalec(x):
    return 0.5 * zad2_muc(x)

def zad2_clipcomplc(x):
    return min(0.75, zad2_complc(x))

zad2_t1 = np.linspace(-4, 4, 1000)
zad2_t2 = np.linspace(-1, 3, 1000)

plt.figure()
plt.xlim((-4, 4))
plt.ylim((0, 1))
plt.plot(zad2_t1, [zad2_mua(x) for x in zad2_t1])
plt.grid(which='both', color='grey', linewidth=1, linestyle='-', alpha=0.2)
plt.savefig('NM januar 2019 zadatak 2 mua.svg')

plt.figure()
plt.xlim((-4, 4))
plt.ylim((-0.1, 1.1))
plt.plot(zad2_t1, [zad2_mub(x) for x in zad2_t1])
plt.grid(which='both', color='grey', linewidth=1, linestyle='-', alpha=0.2)
plt.savefig('NM januar 2019 zadatak 2 mub.svg')

plt.figure()
plt.xlim((-1, 3))
plt.ylim((0, 1.1))
plt.plot(zad2_t2, [zad2_muc(x) for x in zad2_t2])
plt.grid(which='both', color='grey', linewidth=1, linestyle='-', alpha=0.2)
plt.savefig('NM januar 2019 zadatak 2 muc.svg')

plt.figure()
plt.xlim((-4, 4))
plt.ylim((0, 1.1))
plt.plot(zad2_t1, [zad2_union(x) for x in zad2_t1])
plt.grid(which='both', color='grey', linewidth=1, linestyle='-', alpha=0.2)
plt.savefig('NM januar 2019 zadatak 2a A unija B.svg')

plt.figure()
plt.xlim((-4, 4))
plt.ylim((-0.1, 1.1))
plt.plot(zad2_t1, [zad2_complb(x) for x in zad2_t1])
plt.grid(which='both', color='grey', linewidth=1, linestyle='-', alpha=0.2)
plt.savefig('NM januar 2019 zadatak 2a komplement B.svg')

plt.figure()
plt.xlim((-1, 3))
plt.ylim((-0.1, 1))
plt.plot(zad2_t2, [zad2_complc(x) for x in zad2_t2])
plt.grid(which='both', color='grey', linewidth=1, linestyle='-', alpha=0.2)
plt.savefig('NM januar 2019 zadatak 2a komplement C.svg')

plt.figure()
plt.xlim((-1, 3))
plt.ylim((0, 0.6))
plt.plot(zad2_t2, [zad2_scalec(x) for x in zad2_t2])
plt.grid(which='both', color='grey', linewidth=1, linestyle='-', alpha=0.2)
plt.savefig('NM januar 2019 zadatak 2b.svg')

plt.figure()
plt.xlim((-1, 3))
plt.ylim((-0.1, 0.8))
plt.plot(zad2_t2, [zad2_clipcomplc(x) for x in zad2_t2])
plt.grid(which='both', color='grey', linewidth=1, linestyle='-', alpha=0.2)
plt.savefig('NM januar 2019 zadatak 2d.svg')

plt.show()
