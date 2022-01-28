#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "procheap.h"

void
heap_init(struct proc_heap* heap, prioritize_func prioritize)
{
  heap->size = 0;
  heap->prioritize = prioritize;
  for (unsigned i = 0; i < NPROC; ++i)
  {
    heap->data[i] = 0;
  }
  initlock(&heap->lock, "heap_lock");
}

int
left_child(int parent)
{
  return parent * 2 + 1;
}

int
right_child(int parent)
{
  return parent * 2 + 2;
}

int
parent(int child)
{
  return (child - 1) / 2;
}

struct proc*
heap_pop(struct proc_heap* heap, uint t)
{
  acquire(&heap->lock);
  if (heap->size == 0)
  {
    release(&heap->lock);
    return 0;
  }
  --heap->size;
  struct proc* ret = heap->data[0];
  heap->data[0] = heap->data[heap->size];
  heap->data[heap->size] = 0;
  int curr_index = 0;
  while (left_child(curr_index) < heap->size)
  {
    int left = left_child(curr_index);
    int right = right_child(curr_index);
    struct proc* curr_value = heap->data[curr_index];
    int bigger_left = heap->prioritize(heap->data[left], curr_value);
    int bigger_right = (right < heap->size) ?
      heap->prioritize(heap->data[right], curr_value) :
      0;
    if (bigger_left && bigger_right) {
      if (heap->prioritize(heap->data[left], heap->data[right]))
      {
        bigger_right = 0;
      }
    }
    if (bigger_left)
    {
      heap->data[curr_index] = heap->data[left];
      heap->data[left] = curr_value;
      curr_index = left;
    }
    else if (bigger_right)
    {
      heap->data[curr_index] = heap->data[right];
      heap->data[right] = curr_value;
      curr_index = right;
    }
    else
    {
      break;
    }
  }
  ret->last_scheduler_ticks = t;
  release(&heap->lock);
  return ret;
}

struct proc*
heap_top(struct proc_heap* heap)
{
  acquire(&heap->lock);
  struct proc* ret = heap->data[0];
  release(&heap->lock);
  return ret;
}

int
heap_insert(struct proc_heap* heap, struct proc* p, uint t)
{
  acquire(&heap->lock);
  if (heap->size == NPROC)
  {
    release(&heap->lock);
    return -1;
  }
  p->last_scheduler_ticks = t;
  heap->data[heap->size] = p;
  int curr_index = heap->size;
  ++heap->size;
  while (curr_index != 0)
  {
    int parent_index = parent(curr_index);
    if (heap->prioritize(p, heap->data[parent_index]))
    {
      heap->data[curr_index] = heap->data[parent_index];
      heap->data[parent_index] = p;
      curr_index = parent_index;
    }
    else
    {
      break;
    }
  }
  release(&heap->lock);
  return 0;
}

int
heap_reprioritize(struct proc_heap* heap, prioritize_func prioritize)
{
  acquire(&heap->lock);
  heap->prioritize = prioritize;
  int old_size = heap->size;
  heap->size = 0;
  for (int i = 0; i < old_size; ++i)
  {
    if (heap_insert(heap, heap->data[i], heap->data[i]->last_scheduler_ticks) < 0)
    {
      release(&heap->lock);
      return -1;
    }
  }
  release(&heap->lock);
  return 0;
}
