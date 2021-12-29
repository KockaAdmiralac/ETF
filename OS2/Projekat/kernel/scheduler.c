#include "types.h"
#include "riscv.h"
#include "scheduler.h"
#include "defs.h"
#include "procheap.h"

struct proc_heap scheduled_procs;
enum scheduler_algorithm_t scheduler_algorithm = SCHED_ALG_DEFAULT;
int scheduler_algorithm_alpha = SCHED_DEFAULT_ALPHA;
struct spinlock scheduler_algorithm_lock;

int
prioritize_first_come_first_serve(struct proc* proc1, struct proc* proc2)
{
  // The process which entered first, gets in first
  return proc1->scheduler_entry_ticks < proc2->scheduler_entry_ticks;
}

int
prioritize_shortest_job_first(struct proc* proc1, struct proc* proc2)
{
  return (proc1->tau - proc1->cpu_burst_ticks) < (proc2->tau - proc2->cpu_burst_ticks);
}

int
prioritize_completely_fair_scheduler(struct proc* proc1, struct proc* proc2)
{
  return proc1->cpu_burst_ticks < proc2->cpu_burst_ticks;
}

static prioritize_func prioritization_algorithms[] = {
[SCHED_ALG_FCFS] = prioritize_first_come_first_serve,
[SCHED_ALG_SJF]  = prioritize_shortest_job_first,
[SCHED_ALG_CFS]  = prioritize_completely_fair_scheduler
};

void update_first_come_first_serve(struct proc* p)
{
  p->quant = 0;
}

void update_shortest_job_first(struct proc* p)
{
  p->quant = 0;
}

void update_completely_fair_scheduler(struct proc* p)
{
  acquire(&tickslock);
  uint t = ticks;
  release(&tickslock);
  p->quant = (p->scheduler_entry_ticks - t - p->cpu_burst_ticks) / (scheduled_procs.size + 1);
}

static void (*update_algorithms[])(struct proc*) = {
[SCHED_ALG_FCFS] = update_first_come_first_serve,
[SCHED_ALG_SJF]  = update_shortest_job_first,
[SCHED_ALG_CFS]  = update_completely_fair_scheduler
};

struct proc*
scheduler_get(void)
{
  acquire(&scheduler_algorithm_lock);
  struct proc* p = heap_pop(&scheduled_procs);
  if (p == 0)
  {
    release(&scheduler_algorithm_lock);
    return 0;
  }
  update_algorithms[scheduler_algorithm](p);
  release(&scheduler_algorithm_lock);
  return p;
}

int
scheduler_put(struct proc* proc, int was_blocked)
{
  acquire(&scheduler_algorithm_lock);
  int alpha = scheduler_algorithm_alpha;
  release(&scheduler_algorithm_lock);
  if (was_blocked)
  {
    proc->tau = (alpha * proc->tau + (100 - alpha) * proc->cpu_burst_ticks) / 100;
    proc->cpu_burst_ticks = 0;
  }
  if (proc == 0)
  {
    panic("scheduler put null");
    return -1;
  }
  if (heap_insert(&scheduled_procs, proc) < 0)
  {
    panic("scheduler put full");
    return -1;
  }
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
  acquire(&scheduler_algorithm_lock);
  scheduler_algorithm = new_algorithm;
  scheduler_algorithm_alpha = alpha;
  if (heap_reprioritize(&scheduled_procs, prioritization_algorithms[new_algorithm]) < 0)
  {
    panic("heap reprioritize fail");
    release(&scheduler_algorithm_lock);
    return;
  }
  release(&scheduler_algorithm_lock);
}

void
scheduler_init(void)
{
  heap_init(&scheduled_procs, prioritization_algorithms[SCHED_ALG_DEFAULT]);
  initlock(&scheduler_algorithm_lock, "scheduler_algorithm");
}
