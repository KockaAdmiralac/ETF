#include "param.h"
#include "spinlock.h"
#include "proc.h"

typedef int (*prioritize_func)(struct proc*, struct proc*);

struct proc_heap
{
  struct proc* data[NPROC];
  int size;
  struct spinlock lock;
  // Returns 1 if a > b
  int (*prioritize)(struct proc*, struct proc*);
};

void heap_init(struct proc_heap*, prioritize_func);
struct proc* heap_pop(struct proc_heap*, uint);
struct proc* heap_top(struct proc_heap*);
int heap_insert(struct proc_heap*, struct proc*, uint);
int heap_reprioritize(struct proc_heap*, prioritize_func);
