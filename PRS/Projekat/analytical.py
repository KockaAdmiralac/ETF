from csv import writer
from os import makedirs
from matplotlib import pyplot as plt
from numpy.typing import NDArray
from params import *
from typing import Iterable, List, Tuple
import numpy as np

def find_flows(K: int) -> NDArray:
    I = np.identity(4 + K)
    P = np.append(P_base, [[0.5 / K] * K] * 4, 1)
    P = np.append(P, [[0] * (4 + K)] * K, 0)
    A = np.array([1] + [0] * (3 + K)).transpose()
    L = np.linalg.inv(I - P.transpose()) * A
    return L[:, 0]

def get_var_labels(prefix: str, K: int):
    return [f'{prefix}p', f'{prefix}d1', f'{prefix}d2', f'{prefix}d3'] + [f'{prefix}dk{i + 1}' for i in range(K)]

def write_flows(filename: str, L: List[NDArray]):
    with open(filename, 'w', newline='', encoding='utf-8') as csv_file:
        csv_writer = writer(csv_file, 'excel')
        csv_writer.writerow(get_var_labels('λ', len(L[-1]) - 4))
        csv_writer.writerows(L)

def find_amax(L: NDArray) -> Tuple[float, str]:
    lp, ld1, ld2, ld3, *ldk = L
    amax = float('inf')
    weakest_link = '?'
    if 1/Sp/lp < amax:
        weakest_link = 'P'
        amax = 1/Sp/lp
    if 1/Sd1/ld1 < amax:
        weakest_link = 'D1'
        amax = 1/Sd1/ld1
    if 1/Sd2/ld2 < amax:
        weakest_link = 'D2'
        amax = 1/Sd2/ld2
    if 1/Sd3/ld3 < amax:
        weakest_link = 'D3'
        amax = 1/Sd3/ld3
    if 1/Sdk/ldk[0] < amax:
        weakest_link = 'DK'
        amax = 1/Sdk/ldk[0]
    return amax, weakest_link

def plot_amaxes(filename: str, amaxes: List[float]):
    plt.figure()
    plt.title('Zavisnost $\\alpha_{max}$ od $K$')
    plt.xlabel('$K$')
    plt.xticks(K_range)
    plt.ylabel('$\\alpha_{max}$ [$s^{-1}$]')
    plt.plot(K_range, amaxes)
    plt.scatter(K_range, amaxes, color='red')
    plt.savefig(filename)

def get_parameters(L: NDArray, amax: float, r: float) -> Tuple[NDArray, NDArray, NDArray, float]:
    alpha = amax * r
    X = alpha * L
    K = len(L) - 4
    mu = np.array([1/Sp, 1/Sd1, 1/Sd2, 1/Sd3] + [1/Sdk] * K)
    U = X / mu
    J = U / (1 - U)
    # ???
    T = sum(J) / alpha
    return U, X, J, T

def write_results(filename: str, results: List[Tuple[int, float, Iterable, Iterable, Iterable, float]]):
    with open(filename, 'w', newline='', encoding='utf-8') as csv_file:
        K_max = max(K_range)
        csv_writer = writer(csv_file, 'excel')
        csv_writer.writerow(['K', 'r', 'T'] + get_var_labels('U', K_max) + get_var_labels('X', K_max) + get_var_labels('J', K_max))
        for result in results:
            K, r, U, X, J, T = result
            padd = [0 for i in range(K_max - K)]
            csv_writer.writerow([K, r, T, *U, *padd, *X, *padd, *J, *padd])

def plot_results(filename: str, results: List[Tuple[int, float, NDArray]], label: str):
    plt.figure(figsize=(8, 6))
    for r_idx, r in enumerate(r_range):
        plt.subplot(len(r_range) // 2, 2, r_idx + 1)
        results_r = [result for result in results if result[1] == r]
        plt.title(f'$r = {r}$')
        plt.xlabel('$K$')
        plt.xticks(K_range)
        plt.ylabel(f'${label}$')
        labels = get_var_labels(label, 1)
        for index, l in enumerate(labels):
            result = [result[2][index] for result in results_r]
            plt.plot(K_range, result, label=l)
            plt.scatter(K_range, result)
        plt.legend()
    plt.savefig(filename)

def plot_response(filename: str, results: List[Tuple[int, float, float]]):
    plt.figure(figsize=(8, 6))
    for r_idx, r in enumerate(r_range):
        plt.subplot(len(r_range) // 2, 2, r_idx + 1)
        results_r = [result for result in results if result[1] == r]
        plt.title(f'$r = {r}$')
        plt.xlabel('$K$')
        plt.xticks(K_range)
        plt.ylabel('$T$')
        result = [result[2] for result in results_r]
        plt.plot(K_range, result)
        plt.scatter(K_range, result)
    plt.savefig(filename)

if __name__ == '__main__':
    flows = [find_flows(i) for i in K_range]
    makedirs('results', exist_ok=True)
    write_flows('results/flows_analytical.csv', flows)
    amaxes_weakest_links = [find_amax(l) for l in flows]
    amaxes = [awl[0] for awl in amaxes_weakest_links]
    weakest_links = [awl[1] for awl in amaxes_weakest_links]
    plot_amaxes('results/amaxes_analytical.svg', amaxes)
    print(weakest_links)
    results = []
    for i, K in enumerate(K_range):
        for r in r_range:
            results.append([K, r, *get_parameters(flows[i], amaxes[i], r)])
    write_results('results/results_analytical.csv', results)
    plot_results('results/usage_analytical.svg', [(r[0], r[1], r[2]) for r in results], 'U')
    plot_results('results/response_analytical.svg', [(r[0], r[1], r[4]/r[3]) for r in results], 'T')
    plot_response('results/system_response_analytical.svg', [(r[0], r[1], r[5]) for r in results])
