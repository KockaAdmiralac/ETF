from typing import Callable
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

def setup():
    matplotlib.use('pgf')
    matplotlib.rcParams.update({
        'font.family': 'serif',
        'pgf.rcfonts': False,
        'pgf.texsystem': 'pdflatex',
        'text.usetex': True
    })

VR = 2.5
Vcc = 5
Vd = 0.7
def vi1(vg: float) -> float:
    if -3.5 <= vg <= -2.5:
        return 2 * (VR - vg)
    elif -2.5 < vg <= 1.25:
        return -4 * vg
    elif 1.25 < vg <= 3.5:
        return -4 * (vg + VR) / 3
    else:
        return 0

def vi2(vg: float) -> float:
    if 0 <= vg <= 1.64:
        return 2 * vg
    elif 1.64 < vg <= 4:
        return vg/3 + Vcc/2 + Vd/3
    else:
        return 0

def coefficient(x1: float, x2: float, coord_x: float, coord_y: float, round_to: int, vi: Callable[[float], float]) -> None:
    plt.annotate(('~{:.' + str(round_to) + 'f}').format((vi(x2) - vi(x1)) / (x2 - x1)), (coord_x, coord_y))

def setup_plot(low: float, high: float, vi: Callable[[float], float]):
    x = np.linspace(low, high, int(high - low) * 10)
    y = [vi(vg) for vg in x]
    plt.plot(x, y)
    plt.xlabel('$v_G$ [V]')
    plt.ylabel('$v_i$ [V]')
    plt.grid(True)
    plt.title('Zavisnost $v_i$ od $v_G$')

def prvi():
    setup_plot(-3.5, 3.5, vi1)
    plt.axis([-3.5, 3.5, -8, 12])
    plt.xticks([(a - 7) / 2 for a in range(15)])
    plt.yticks([a - 8 for a in range(21)])
    coefficient(-3.5, -2.5, -3, 11, 0, vi1)
    coefficient(-2.5, 1.25, -0.5, 3, 0, vi1)
    coefficient(1.25, 3.5, 2.5, -6, 2, vi1)
    # plt.show()
    plt.savefig('Grafik1.pgf')
    plt.close()

def drugi():
    setup_plot(0, 4, vi2)
    plt.axis([0, 4, 0, 4.1])
    coefficient(0, 1.64, 1.5, 2, 0, vi2)
    coefficient(1.64, 4, 3, 3.5, 2, vi2)
    # plt.show()
    plt.savefig('Grafik2.pgf')
    plt.close()

setup()
prvi()
drugi()
