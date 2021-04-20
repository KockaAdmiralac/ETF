#include <stdlib.h>

typedef struct {
    void *base;
    size_t size;
} PCB;
int mem_allocate_at(size_t sz, void* at);
int mem_allocate(size_t sz, void** location);
void mem_free(void* at, size_t sz);
void mem_copy(void* from, void* to, size_t sz);

int extend (PCB* pcb, size_t by) {
    if (pcb == NULL) {
        return -1;
    }
    if (mem_allocate_at(by, pcb->base + pcb->size) == 0) {
        pcb->size += by;
        return 0;
    }
    void *newLocation;
    if (mem_allocate(pcb->size + by, &newLocation) != 0) {
        return -1;
    }
    if (pcb->base != newLocation) {
        mem_copy(pcb->base, newLocation, pcb->size);
        mem_free(pcb->base, pcb->size);
        pcb->base = newLocation;
    }
    pcb->size += by;
    return 0;
}
