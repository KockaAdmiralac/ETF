#include "types.h"
#include "riscv.h"
#include "scheduler.h"
#include "defs.h"
#include "procheap.h"

struct proc_heap scheduled_procs;
struct proc_heap scheduled_procs_by_cpu[NCPU];
enum scheduler_algorithm_t scheduler_algorithm = SCHED_ALG_DEFAULT;
int scheduler_algorithm_alpha = SCHED_DEFAULT_ALPHA;
struct spinlock scheduler_algorithm_lock;

int
prioritize_shortest_job_first(struct proc* proc1, struct proc* proc2)
{
  return proc1->tau < proc2->tau;
}

int
prioritize_completely_fair_scheduler(struct proc* proc1, struct proc* proc2)
{
  return proc1->execution_time < proc2->execution_time;
}

static prioritize_func prioritization_algorithms[] = {
[SCHED_ALG_SJF]    = prioritize_shortest_job_first,
[SCHED_ALG_SJF_P] = prioritize_shortest_job_first,
[SCHED_ALG_CFS]    = prioritize_completely_fair_scheduler
};

void update_shortest_job_first(struct proc* p, __attribute__((unused)) uint t)
{
  p->quant = 0;
}

void update_completely_fair_scheduler(struct proc* p, uint t)
{
  p->quant = (t - p->old_last_scheduler_ticks) / (scheduled_procs.size + 1);
  if (p->quant <= 0) {
    p->quant = 1;
  } else {
    int a = 0;
  }
}

static void (*update_algorithms[])(struct proc*, uint) = {
[SCHED_ALG_SJF]    = update_shortest_job_first,
[SCHED_ALG_SJF_P] = update_shortest_job_first,
[SCHED_ALG_CFS]    = update_completely_fair_scheduler
};

struct proc*
scheduler_get(void)
{
#ifdef SCHEDULER_THREADSAFE
  acquire(&scheduler_algorithm_lock);
#endif
  enum scheduler_algorithm_t alg = scheduler_algorithm;
#ifdef SCHEDULER_THREADSAFE
  release(&scheduler_algorithm_lock);
  acquire(&tickslock);
#endif
  uint t = ticks;
#ifdef SCHEDULER_THREADSAFE
  release(&tickslock);
#endif
#ifdef SCHEDULER_MULTICORE
  int id = cpuid();
  struct proc* p1 = heap_top(&scheduled_procs);
  struct proc* p2 = heap_top(&scheduled_procs_by_cpu[id]);
  struct proc* p;
  prioritize_func prioritize = prioritization_algorithms[alg];
  if (p1 == 0 && p2 == 0) {
    return 0;
  } else if (p1 == 0) {
    p = heap_pop(&scheduled_procs_by_cpu[id], t);
  } else if (p2 == 0) {
    p = heap_pop(&scheduled_procs, t);
  } else if (prioritize(p1, p2)) {
    p = heap_pop(&scheduled_procs, t);
  } else {
    p = heap_pop(&scheduled_procs_by_cpu[id], t);
  }
  // Just in case, there are possible race conditions here.
  if (p == 0)
  {
    return 0;
  }
#else
  struct proc* p = heap_pop(&scheduled_procs, t);
  if (p == 0)
  {
    return 0;
  }
#endif
  update_algorithms[alg](p, t);
  return p;
}

int
scheduler_put(struct proc* proc, int was_blocked)
{
  if (proc == 0)
  {
    panic("scheduler put null");
    return -1;
  }
#ifdef SCHEDULER_THREADSAFE
  acquire(&scheduler_algorithm_lock);
#endif
  int alpha = scheduler_algorithm_alpha;
#ifdef SCHEDULER_THREADSAFE
  release(&scheduler_algorithm_lock);
  int holding_ticks = holding(&tickslock);
  if (!holding_ticks)
    acquire(&tickslock);
#endif
  uint t = ticks;
#ifdef SCHEDULER_THREADSAFE
  if (!holding_ticks)
    release(&tickslock);
#endif
  proc->cpu_burst_ticks += t - proc->last_scheduler_ticks;
  if (was_blocked)
  {
    proc->tau = ((100 - alpha) * proc->tau + alpha * proc->cpu_burst_ticks) / 100;
    proc->execution_time += proc->cpu_burst_ticks;
    proc->cpu_burst_ticks = 0;
  }
#ifdef SCHEDULER_MULTICORE
  int min_heap_size = NPROC + 1;
  for (int i = 0; i < NCPU; ++i) {
    int heap_size = scheduled_procs_by_cpu[i].size;
    if (heap_size < min_heap_size) {
      min_heap_size = heap_size;
    }
  }
  int id = cpuid();
  int insert_result;
  if (scheduled_procs_by_cpu[id].size <= min_heap_size) {
    insert_result = heap_insert(&scheduled_procs_by_cpu[id], proc, t);
  } else {
    insert_result = heap_insert(&scheduled_procs, proc, t);
  }
  if (insert_result < 0)
  {
    panic("scheduler put full");
    return -1;
  }
#else
  if (heap_insert(&scheduled_procs, proc, t) < 0)
  {
    panic("scheduler put full");
    return -1;
  }
#endif
  return 0;
}

void
scheduler_set_algorithm(enum scheduler_algorithm_t new_algorithm, int alpha)
{
  if (new_algorithm <= SCHED_ALG_START || new_algorithm >= SCHED_ALG_END)
  {
    panic("scheduler algorithm invalid");
    return;
  }
#ifdef SCHEDULER_THREADSAFE
  acquire(&scheduler_algorithm_lock);
#endif
  scheduler_algorithm_alpha = alpha;
  if (scheduler_algorithm == new_algorithm)
  {
#ifdef SCHEDULER_THREADSAFE
    release(&scheduler_algorithm_lock);
#endif
    return;
  }
  scheduler_algorithm = new_algorithm;
#ifdef SCHEDULER_THREADSAFE
  release(&scheduler_algorithm_lock);
#endif
  if (heap_reprioritize(&scheduled_procs, prioritization_algorithms[new_algorithm]) < 0)
  {
    panic("heap reprioritize fail");
  }
#ifdef SCHEDULER_MULTICORE
  for (int i = 0; i < NCPU; ++i) {
    if (heap_reprioritize(&scheduled_procs_by_cpu[i], prioritization_algorithms[new_algorithm]) < 0)
    {
      panic("heap reprioritize fail");
    }
  }
#endif
}

int
scheduler_can_preempt(struct proc* p)
{
#ifdef SCHEDULER_THREADSAFE
  acquire(&scheduler_algorithm_lock);
#endif
  enum scheduler_algorithm_t alg = scheduler_algorithm;
#ifdef SCHEDULER_THREADSAFE
  release(&scheduler_algorithm_lock);
#endif
  if (alg != SCHED_ALG_SJF_P)
  {
    return 0;
  }
  prioritize_func prioritize = prioritization_algorithms[alg];
#ifdef SCHEDULER_MULTICORE
  int id = cpuid();
  struct proc* np1 = heap_top(&scheduled_procs);
  struct proc* np2 = heap_top(&scheduled_procs_by_cpu[id]);
  if (np1 == 0 && np2 == 0)
  {
    return 0;
  }
  if (np1 == 0)
  {
    return prioritize(np2, p);
  }
  if (np2 == 0)
  {
    return prioritize(np1, p);
  }
  return prioritize(np1, p) || prioritize(np2, p);
#else
  struct proc* np = heap_top(&scheduled_procs);
  if (np == 0)
  {
    return 0;
  }
  // Possible race condition, but this is an optimization anyway.
  return prioritize(np, p);
#endif
}

void
scheduler_init(void)
{
  heap_init(&scheduled_procs, prioritization_algorithms[SCHED_ALG_DEFAULT]);
#ifdef SCHEDULER_MULTICORE
  for (int i = 0; i < NCPU; ++i) {
    heap_init(&scheduled_procs_by_cpu[i], prioritization_algorithms[SCHED_ALG_DEFAULT]);
  }
#endif
  initlock(&scheduler_algorithm_lock, "scheduler_algorithm");
}
