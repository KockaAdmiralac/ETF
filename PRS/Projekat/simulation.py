from analytical import find_amax, find_flows, write_results
from argparse import ArgumentParser
from collections import deque
from itertools import product
from math import exp
from multiprocessing import cpu_count, Pool
from params import *
from random import uniform
from tqdm import tqdm
from typing import Iterable, List, Optional, Tuple
import numpy as np

SEC_TO_TICKS = 1000 * 4

SimulationResult = Tuple[int, float, Iterable[float], Iterable[float], Iterable[float], float]

class PoissonProcess:
    def __init__(self, flow: int):
        l = 1 / flow
        self.p0: float = exp(-l)

    def get(self) -> int:
        num = uniform(0.0, 1.0)
        if 0 <= num <= self.p0:
            return 0
        return 1

class Server:
    def __init__(self, processing_time: int, input_flow: int = 0):
        self.processing: PoissonProcess = PoissonProcess(processing_time)
        self.input_flow: Optional[PoissonProcess] = None if input_flow == 0 else PoissonProcess(input_flow)
        self.probabilities: List[float] = []
        self.connections: List[Server] = []
        self.jobs: deque[int] = deque()
        self.stats_num_jobs: List[int] = []
        self.stats_num_jobs_total: List[int] = []
        self.stats_has_jobs: List[int] = []
        self.stats_has_jobs_total: List[int] = []
        self.stats_done_jobs = 0
        self.stats_done_jobs_total: List[int] = []

    def connect(self, server: 'Server', probability: float):
        self.connections.append(server)
        max_probability = 0 if len(self.probabilities) == 0 else self.probabilities[-1]
        new_probability = min(max_probability + probability, 1.0)
        if new_probability > 1.0:
            raise ValueError('Total transition probability over 1!')
        self.probabilities.append(new_probability)

    def update(self, tick: int, stats_response_time: List[int]):
        # Update the number of jobs based on the input flow
        if self.input_flow is not None:
            if self.input_flow.get() == 1:
                self.jobs.append(tick)
        # Update the number of jobs based on the number of processed jobs
        if len(self.jobs) > 0:
            if self.processing.get() == 1:
                # self.processed = 0
                job = self.jobs.popleft()
                self.stats_done_jobs += 1
                # Determine where the job goes
                if len(self.probabilities) > 0:
                    # The job goes to the next server
                    next_server: Optional[Server] = None
                    random_number = uniform(0.0, 1.0)
                    for index, probability in enumerate(self.probabilities):
                        if probability >= random_number:
                            next_server = self.connections[index]
                            break
                    if next_server is None:
                        raise ValueError('Could not determine a server to pass the job to!')
                    next_server.jobs.append(job)
                else:
                    # The job goes out of the system
                    stats_response_time.append(tick - job)
        self.stats_num_jobs.append(len(self.jobs))
        self.stats_has_jobs.append(1 if len(self.jobs) > 0 else 0)

    def update_stats(self):
        self.stats_num_jobs_total.append(sum(self.stats_num_jobs))
        self.stats_num_jobs = []
        self.stats_has_jobs_total.append(sum(self.stats_has_jobs))
        self.stats_has_jobs = []
        self.stats_done_jobs_total.append(self.stats_done_jobs)
        self.stats_done_jobs = 0

    def get_stats(self):
        J = sum(self.stats_num_jobs_total) / len(self.stats_num_jobs_total)
        U = sum(self.stats_has_jobs_total) / len(self.stats_has_jobs_total)
        X = sum(self.stats_done_jobs_total) / len(self.stats_done_jobs_total)
        return J, U, X

def sec_to_ticks(seconds: float) -> int:
    return int(seconds * SEC_TO_TICKS)

def simulation(K: int, r: float, time: int) -> SimulationResult:
    amax = find_amax(find_flows(K))[0]
    alpha = r * amax
    input_flow = sec_to_ticks(1 / alpha)
    p = Server(sec_to_ticks(Sp), input_flow)
    d1 = Server(sec_to_ticks(Sd1))
    d2 = Server(sec_to_ticks(Sd2))
    d3 = Server(sec_to_ticks(Sd3))
    dks = [Server(sec_to_ticks(Sdk)) for _ in range(K)]
    p.connect(d1, 0.15)
    p.connect(d2, 0.1)
    p.connect(d3, 0.05)
    p.connect(p, 0.2)
    d1.connect(p, 0.3)
    d1.connect(d1, 0.2)
    d2.connect(p, 0.3)
    d2.connect(d2, 0.2)
    d3.connect(p, 0.3)
    d3.connect(d3, 0.2)
    dk_probability_avg = 0.5 / K
    for i, dk in enumerate(dks):
        dk_probability = (1 - dk_probability_avg * (K - 1)) if i == len(dks) - 1 else dk_probability_avg
        p.connect(dk, dk_probability)
        d1.connect(dk, dk_probability)
        d2.connect(dk, dk_probability)
        d3.connect(dk, dk_probability)
    servers = [p, d1, d2, d3, *dks]
    stats_response_time = []
    for tick in range(time):
        for server in servers:
            server.update(tick, stats_response_time)
        if tick % SEC_TO_TICKS == SEC_TO_TICKS - 1:
            for server in servers:
                server.update_stats()
    Js = []
    Us = []
    Xs = []
    for server in servers:
        J, U, X = server.get_stats()
        Js.append(J / SEC_TO_TICKS)
        Us.append(U / SEC_TO_TICKS)
        Xs.append(X)
    T = sum(stats_response_time) / len(stats_response_time) / SEC_TO_TICKS
    return K, r, Us, Xs, Js, T

def average_results(results: List[SimulationResult]) -> List[SimulationResult]:
    avg_results: List[SimulationResult] = []
    for K in K_range:
        for r in r_range:
            kr_results = [result for result in results if result[0] == K and result[1] == r]
            Us = np.array([result[2] for result in kr_results])
            Xs = np.array([result[3] for result in kr_results])
            Js = np.array([result[4] for result in kr_results])
            Ts = [result[5] for result in kr_results]
            avg_results.append((K, r, np.average(Us, axis=0), np.average(Xs, axis=0), np.average(Js, axis=0), sum(Ts) / len(Ts)))
    return avg_results

if __name__ == '__main__':
    parser = ArgumentParser(description='Simulates an open network for our Computer Systems Performance class project, june 2023.')
    parser.add_argument('-t', '--time', type=int, default=30 * 60, help='simulation time in seconds (default: 30m)')
    parser.add_argument('-it', '--iterations', type=int, default=1, help='number of simulation iterations (default: 1)')
    args = parser.parse_args()
    simulation_time_ticks = sec_to_ticks(args.time)
    results = []
    with Pool(processes=cpu_count()) as pool, tqdm(total=len(K_range) * len(r_range) * args.iterations) as bar:
        jobs = []
        for K, r, _ in product(K_range, r_range, range(args.iterations)):
            jobs.append(pool.apply_async(simulation, (K, r, simulation_time_ticks), callback=lambda res: bar.update()))
        for job in jobs:
            results.append(job.get())
    avg_results = average_results(results)
    write_results(f'results/results_simulation_{args.iterations}.csv', avg_results)
