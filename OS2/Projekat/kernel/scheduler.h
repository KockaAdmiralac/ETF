#include "param.h"

#define SCHED_DEFAULT_ALPHA 50

enum scheduler_algorithm_t
{
  SCHED_ALG_START = 0,

  SCHED_ALG_SJF,
  SCHED_ALG_SJF_P,
  SCHED_ALG_CFS,

  SCHED_ALG_END,
  SCHED_ALG_DEFAULT = 1 // SJF
};

struct proc* scheduler_get(void);
int scheduler_put(struct proc*, int);
void scheduler_set_algorithm(enum scheduler_algorithm_t, int alpha);
int scheduler_can_preempt(struct proc*);
void scheduler_init(void);
