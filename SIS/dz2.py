from matplotlib import pyplot as plt
from scipy.fftpack import fft, fftshift, fftfreq
from scipy.io import wavfile as wav
from scipy.signal import butter, filtfilt
from typing import List
import numpy as np

# Osnovne funkcije za obradu i iscrtavanje
freq_axis = lambda fs, data: fftshift(fftfreq(len(data), 1/fs))
filt = lambda f, x: filtfilt(*f, x)
def filter(n: int, f_gr, fs, ftype='lowpass') -> List[np.ndarray]:
    return butter(n, f_gr / (fs/2), btype=ftype)
def save_wav(file: str, fs: int, x: np.ndarray) -> None:
    wav.write(f'{file}.wav', fs, np.int16(x/np.max(np.abs(x)) * 32767))
def plot_freq(subplot: int, freq: np.ndarray, data: np.ndarray, title: str, xlim: int) -> None:
    plt.subplot(2, 2, subplot)
    plt.plot(freq, fftshift(np.abs(fft(data))))
    plt.gca().set_title(f'$\\left|{title}(j\\omega)\\right|$')
    plt.xlim((-xlim, xlim))
def plot_time(subplot: int, fs: int, time: np.ndarray, title: str) -> None:
    plt.subplot(2, 2, subplot)
    plt.plot(np.linspace(0, len(time)/fs, len(time)), time)
    plt.gca().set_title(f'${title}(t)$')

# Parametri sistema
n = 6
f_lp = 6000
f_c = 12500
f_ch = 21000

# Čitanje ulaznih signala
fs_1, y1 = wav.read('y_1.wav')
fs_2, y2 = wav.read('y_2.wav')

# Konstrukcija filtara, modulatora i osa
flt_lp = filter(n, f_lp, fs_1)
flt_ch = filter(n, f_ch, fs_1)
flt_bp = filter(n, np.array([f_c - f_lp, f_c + f_lp]), fs_1, 'bandpass')
y1_freq = freq_axis(fs_1, y1)
y2_freq = freq_axis(fs_2, y2)
y2_t = np.arange(0, len(y2)/fs_2, 1/fs_2)
mod = np.cos(2 * np.pi * f_c * y2_t)

# Generisanje signala u sistemu
y1n = filt(flt_lp, y1)
y2n = filt(flt_lp, y2)
y2m = y2n * mod
yt = y1n + y2m
yr = filt(flt_ch, yt)
y1r = filt(flt_lp, yr)
y2b = filt(flt_bp, yr)
y2d = y2b * mod
y2r = filt(flt_lp, y2d)

# Iscrtavanje
# Napomena: Dužine zvučnih signala ne moraju da budu iste, ali pošto jesu
# amplitudske karakteristike iscrtavamo koristeći frekvencijsku osu prvog.
plt.figure()
plot_freq(1, y1_freq, y1, 'Y_1', 10000)
plot_freq(2, y2_freq, y2, 'Y_2', 10000)
plot_freq(3, y2_freq, y2m, 'Y_2^m', 20000)
plt.savefig('dz2-1.pgf')
plt.figure()
plot_freq(1, y1_freq, yt, 'Y_T', 20000)
plot_freq(2, y1_freq, yr, 'Y_R', 20000)
plot_freq(3, y2_freq, y2b, 'Y_2^b', 20000)
plot_freq(4, y2_freq, y2d, 'Y_2^d', 20000)
plt.savefig('dz2-2.pgf')
plt.figure()
plot_freq(1, y1_freq, y1r, 'Y_1^r', 10000)
plot_freq(2, y2_freq, y2r, 'Y_2^r', 10000)
plot_time(3, fs_1, y1r, 'y_1^r')
plot_time(4, fs_2, y2r, 'y_2^r')
plt.savefig('dz2-3.pgf')
plt.show()

# Čuvanje izlaznih signala
save_wav('y_2_m', fs_2, y2m)
save_wav('y_t', fs_1, yt)
save_wav('y_r', fs_1, yr)
save_wav('y_2_b', fs_2, y2b)
save_wav('y_2_d', fs_2, y2d)
save_wav('y_1_r', fs_1, y1r)
save_wav('y_2_r', fs_2, y2r)
