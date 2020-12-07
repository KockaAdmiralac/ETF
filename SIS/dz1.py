#!/usr/bin/env python
from matplotlib import pyplot as plt
from scipy.signal import convolve, unit_impulse
import matplotlib
import numpy as np

u = lambda a: np.heaviside(a, 1)
ev = lambda x: lambda n: (x(n) + x(-n))/2
od = lambda x: lambda n: (x(n) - x(-n))/2

godina = 2019
indeks = 368
suma_cifara_godine = sum([int(c) for c in str(godina)])
suma_cifara_indeksa = sum([int(c) for c in str(indeks)])
N = (godina + indeks) % 6
P = (godina + indeks) % 5
Q = (suma_cifara_indeksa + suma_cifara_godine) % 5
R = (suma_cifara_indeksa + suma_cifara_godine) % 3

print('N =', N)
print('P =', P)
print('Q =', Q)
print('R =', R)

# 1. a
x = lambda t: (3 + 0.4 * (t - 0.5)) * (u(t - 0.5) - u(t - 3))
f_1 = lambda t: x((Q + 3) + t)
f_2 = lambda t: x((Q + 3) - t)
f = lambda t: x((Q + 3) - (2 * R + 3) * t)
f_r = lambda t: (4 - (t - 4/7) * 14 / 5) * (u(t - 4/7) - u(t - 13/14))

plt.figure(1)

plt.subplot(2, 2, 1)
plt.gca().set_title('$x(t)$')
plt.xticks(np.arange(0, 4, 0.5))
t_x = np.linspace(0, 4, 100)
plt.plot(t_x, x(t_x))

plt.subplot(2, 2, 2)
plt.gca().set_title('$f_1(t)$')
plt.xticks(np.arange(-7, -3, 0.5))
t_f1 = np.linspace(-7, -3, 100)
plt.plot(t_f1, f_1(t_f1))

plt.subplot(2, 2, 3)
plt.gca().set_title('$f_2(t)$')
plt.xticks(np.arange(3, 7, 0.5))
t_f2 = np.linspace(3, 7, 100)
plt.plot(t_f2, f_2(t_f2))

plt.subplot(2, 2, 4)
plt.gca().set_title('$f(t)$')
plt.xticks(np.arange(0, 1.1, 0.1))
t_f = np.linspace(0, 1, 100)
plt.plot(t_f, f(t_f), label='Generisano $f(t)$')
plt.plot(t_f, f_r(t_f), label='Izračunato $f(t)$')
plt.legend()

plt.savefig('dz1-1-a.pgf')

# 1. b
w = lambda n: -(n + 2) * (u(n + 1) - u(n - 4))
v_1 = lambda n: w(n + 2)
v_2 = lambda n: w(-n + 2)
v = lambda n: 2 * w(-n/3 + 2)
v_r = lambda n: (-10 + 2 * (n + 3)/3) * (u(n + 3) - u(n - 12))

plt.figure(2)

plt.subplot(2, 2, 1)
plt.gca().set_title('$w[n]$')
n_w = np.arange(-5, 5)
plt.xticks(n_w)
plt.plot(n_w, w(n_w))
plt.scatter(n_w, w(n_w))

plt.subplot(2, 2, 2)
plt.gca().set_title('$v_1[n]$')
n_v1 = np.arange(-7, 3)
plt.xticks(n_v1)
plt.plot(n_v1, v_1(n_v1))
plt.scatter(n_v1, v_1(n_v1))

plt.subplot(2, 2, 3)
plt.gca().set_title('$v_2[n]$')
n_v2 = np.arange(-3, 7)
plt.xticks(n_v2)
plt.plot(n_v2, v_2(n_v2))
plt.scatter(n_v2, v_2(n_v2))

plt.subplot(2, 2, 4)
plt.gca().set_title('$v[n]$')
n_v = np.arange(-9, 16, 3)
plt.xticks(n_v)
plt.plot(n_v, v(n_v), label='Generisano $v[n]$')
plt.plot(n_v, v_r(n_v), label='Izračunato $v[n]$')
plt.scatter(n_v, v(n_v))
plt.legend()

plt.savefig('dz1-1-b.pgf')

# 1. c
ev_w = ev(w)
od_w = od(w)
def ev_w_r(n: int) -> float:
    if -1 > n > -4:
        return (n - 2)/2
    elif 1 >= n >= -1:
        return -2
    elif 4 > n > 1:
        return (-n - 2)/2
    else:
        return 0

def od_w_r(n: int) -> float:
    if -1 > n > -4:
        return (2 - n)/2
    elif 1 >= n >= -1:
        return -n
    elif 4 > n > 1:
        return (-n - 2)/2
    else:
        return 0

plt.figure(3)

plt.subplot(2, 2, 1)
plt.gca().set_title('$w[n]$')
n_w = np.arange(-5, 5)
plt.xticks(n_w)
plt.plot(n_w, w(n_w))
plt.scatter(n_w, w(n_w))

plt.subplot(2, 2, 2)
plt.gca().set_title('$Ev \\{w[n]\\}$')
plt.xticks(n_w)
plt.plot(n_w, ev_w(n_w), label='Generisano $Ev \\{w[n]\\}$')
plt.plot(n_w, np.array([ev_w_r(n) for n in n_w]), label='Izračunato $Ev \\{w[n]\\}$')
plt.scatter(n_w, ev_w(n_w))
plt.legend()

plt.subplot(2, 2, 3)
plt.gca().set_title('$Od \\{w[n]\\}$')
plt.xticks(n_w)
plt.plot(n_w, od_w(n_w), label='Generisano $Od \\{w[n]\\}$')
plt.plot(n_w, np.array([od_w_r(n) for n in n_w]), label='Izračunato $Od \\{w[n]\\}$')
plt.scatter(n_w, od_w(n_w))
plt.legend()

plt.savefig('dz1-1-c.pgf')

# 2. a
y = lambda t: -(u(t + 3) - u(t + 1))

def conv_x_y_1(t: float) -> float:
    if -2.5 <= t < -0.5:
        return 14/5 * (t + 5/2) + 2/5 * ((t + 3)**2 - 1/4)
    elif -0.5 <= t < 0:
        return 28/5 + 2/5 * ((t + 3)**2 - (t + 1)**2)
    elif 0 <= t < 2:
        return 14/5 * (2 - t) + 2/5 * (9 - (t + 1)**2)
    else:
        return 0
conv_x_y = lambda t: np.array([-conv_x_y_1(t_i) for t_i in t]) + \
                     (14/5 + 2/5 * (t - 1)) * (u(t - 3/2) - u(t - 4))

plt.figure(4)

plt.subplot(1, 2, 1)
plt.gca().set_title('$x(t) * y(t)$')
t_conv_x_y = np.arange(-5, 5, 0.1)
plt.plot(t_conv_x_y, conv_x_y(t_conv_x_y), label='Izračunato $x(t) * y(t)$')

# 2. b
z = lambda n: u(n + 1) - u(n - 3)
conv_w_z = lambda n: np.array([
    -np.sum([(m + 2) * (u(m + 1) - u(m - 4)) for m in range(ni - 3, ni + 3)
]) for ni in n])

plt.subplot(1, 2, 2)
plt.gca().set_title('$w[n] * z[n]$')
n_conv_w_z = np.arange(-5, 9)
plt.plot(n_conv_w_z, conv_w_z(n_conv_w_z), label='Izračunato $w[n] * z[n]$')
plt.scatter(n_conv_w_z, conv_w_z(n_conv_w_z), label='Izračunato $w[n] * z[n]$')

plt.savefig('dz1-2.pgf')

# 4.
T = 2 * np.pi
omega0 = 2 * np.pi / T
def a(k: int) -> complex:
    if k == 1 or k == -1:
        return 1/4j
    return (1 + (-1)**k)/(2 * np.pi * (1 - k**2))

v = lambda t: np.sin(t) * u(np.sin(t))
vk = lambda k, t: np.real(2 * a(k) * np.exp(1j * k * omega0 * t))
v1 = lambda t: a(0) + vk(1, t)

plt.figure(5)

# 4. b
plt.subplot(2, 2, 1)
plt.gca().set_title('$v(t)$, $v_1(t)$ i $v_2(t)$')
t_v = np.linspace(-2 * np.pi, 4 * np.pi, 1000)
plt.plot(t_v, v(t_v), label='$v(t)$')
plt.plot(t_v, vk(1, t_v), label='$v_1(t)$')
plt.plot(t_v, vk(2, t_v), label='$v_2(t)$')
plt.legend()

# 4. c
plt.subplot(2, 2, 2)
plt.gca().set_title('$v(t)$ i $\\hat{v}_1(t)$')
plt.plot(t_v, v(t_v), label='$v(t)$')
plt.plot(t_v, v1(t_v), label='$\\hat{v}_1(t)$')
plt.legend()

# 4. d
plt.subplot(2, 2, 3)
plt.gca().set_title('Zavisnost $|a_k|$ od $k$')
plt.plot([np.abs(a(k)) for k in range(0, 4)])
plt.scatter(range(0, 4), [np.abs(a(k)) for k in range(0, 4)])

plt.savefig('dz1-4.pgf')

plt.show()
