from matplotlib import pyplot as plt
import numpy as np

plt.xlim(0, 70)
plt.ylim(0, 1)
plt.xlabel('Број пакета у баферу')
plt.ylabel('Вероватноћа одбацивања пакета')
plt.plot([20, 30, 40, 40.00001], [0, 0.1, 0.2, 1.0], color='r', label='AF23')
plt.plot([30, 40, 50, 50.00001], [0, 0.1, 0.2, 1.0], color='b', label='AF22')
plt.plot([40, 50, 60, 60.00001], [0, 0.1, 0.2, 1.0], color='g', label='AF21')
plt.plot([0, 70], [0.2, 0.2], color='black', linestyle='dotted')
plt.legend()
plt.savefig('grafik.svg')
