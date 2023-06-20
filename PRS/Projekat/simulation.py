from analytical import find_amax, find_flows, write_results
from argparse import ArgumentParser
from collections import deque
from dataclasses import dataclass, field
from enum import IntEnum
from itertools import product
from math import exp
from multiprocessing import cpu_count, Pool
from params import *
from queue import PriorityQueue
from random import uniform
from tqdm import tqdm
from typing import Iterable, List, Optional, Tuple
import numpy as np

SimulationResult = Tuple[int, float, Iterable[float], Iterable[float], Iterable[float], float]

class PoissonProcess:
    def __init__(self, beta: int):
        self.beta = beta

    def next_event(self) -> float:
        return np.random.exponential(self.beta)

class EventType(IntEnum):
    INPUT_FLOW = 0
    PROCESSING = 1

@dataclass(order=True)
class Event:
    time: float
    type: EventType = field(compare=False)
    server: Optional['Server']

class Server:
    def __init__(self, processing_time: float):
        self.processing: PoissonProcess = PoissonProcess(processing_time)
        self.probabilities: List[float] = []
        self.connections: List[Server] = []
        self.jobs: deque[float] = deque()
        self.last_job_update: float = 0.0
        self.stats_num_jobs: float = 0.0
        self.stats_has_jobs: float = 0.0
        self.stats_done_jobs = 0

    def connect(self, server: 'Server', probability: float):
        self.connections.append(server)
        max_probability = 0 if len(self.probabilities) == 0 else self.probabilities[-1]
        new_probability = min(max_probability + probability, 1.0)
        if new_probability > 1.0:
            raise ValueError('Total transition probability over 1!')
        self.probabilities.append(new_probability)

    def add_job(self, job: float, ctime: float, events: PriorityQueue[Event]):
        if len(self.jobs) == 0:
            events.put(Event(ctime + self.processing.next_event(), EventType.PROCESSING, self))
        dt = ctime - self.last_job_update
        self.last_job_update = ctime
        self.stats_num_jobs += len(self.jobs) * dt
        self.stats_has_jobs += (1.0 if len(self.jobs) > 0 else 0.0) * dt
        self.jobs.append(job)

    def done_job(self, ctime: float, events: PriorityQueue[Event], stats_response_time: List[float]):
        dt = ctime - self.last_job_update
        self.last_job_update = ctime
        self.stats_num_jobs += len(self.jobs) * dt
        self.stats_has_jobs += (1.0 if len(self.jobs) > 0 else 0.0) * dt
        job = self.jobs.popleft()
        self.stats_done_jobs += 1
        next_server: Optional[Server] = None
        # Determine where the job goes
        if len(self.probabilities) > 0:
            # The job goes to the next server
            random_number = uniform(0.0, 1.0)
            for index, probability in enumerate(self.probabilities):
                if probability >= random_number:
                    next_server = self.connections[index]
                    break
            if next_server is None:
                raise ValueError('Could not determine a server to pass the job to!')
            next_server.add_job(job, ctime, events)
        else:
            # The job goes out of the system
            stats_response_time.append(ctime - job)
        if len(self.jobs) > 0 and not (next_server == self and len(self.jobs) == 1):
            events.put(Event(ctime + self.processing.next_event(), EventType.PROCESSING, self))

    def get_stats(self, ctime: float):
        J = self.stats_num_jobs / ctime
        U = self.stats_has_jobs / ctime
        X = self.stats_done_jobs / ctime
        return J, U, X

def simulation(K: int, r: float, time: int) -> SimulationResult:
    amax = find_amax(find_flows(K))[0]
    alpha = r * amax
    # Create all servers.
    p = Server(Sp)
    d1 = Server(Sd1)
    d2 = Server(Sd2)
    d3 = Server(Sd3)
    dks = [Server(Sdk) for _ in range(K)]
    # Connect the servers.
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
    # Start event-based simulation.
    stats_response_time: List[float] = []
    events: PriorityQueue[Event] = PriorityQueue()
    input_flow = PoissonProcess(1 / alpha)
    events.put(Event(input_flow.next_event(), EventType.INPUT_FLOW, None))
    ctime = 0.0
    while ctime < time and not events.empty():
        event = events.get()
        ctime = event.time
        if event.type == EventType.INPUT_FLOW:
            p.add_job(ctime, ctime, events)
            events.put(Event(ctime + input_flow.next_event(), EventType.INPUT_FLOW, None))
        else:
            event.server.done_job(ctime, events, stats_response_time)
    # Collect simulation results.
    Js = []
    Us = []
    Xs = []
    servers = [p, d1, d2, d3, *dks]
    for server in servers:
        J, U, X = server.get_stats(ctime)
        Js.append(J)
        Us.append(U)
        Xs.append(X)
    T = sum(stats_response_time) / len(stats_response_time)
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
    results = []
    with Pool(processes=cpu_count()) as pool, tqdm(total=len(K_range) * len(r_range) * args.iterations) as bar:
        jobs = []
        for K, r, _ in product(K_range, r_range, range(args.iterations)):
            jobs.append(pool.apply_async(simulation, (K, r, args.time), callback=lambda res: bar.update()))
        for job in jobs:
            results.append(job.get())
    avg_results = average_results(results)
    write_results(f'results/results_simulation_{args.iterations}.csv', avg_results)
