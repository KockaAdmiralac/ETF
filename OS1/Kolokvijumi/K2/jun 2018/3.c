#include <stdlib.h>

typedef enum {pageFault, opDenied} AddrExcKind;
typedef struct {
    unsigned long startingPage;
    unsigned long size;
    SegDesc *next, *prev;
    short rwx;
} SegDesc;
typedef struct {
    SegDesc *segDesc;
} PCB;
const int MEM_ACCESS_FAULT = 1;
const int LOAD_PAGE = 1;
const int COPY_ON_WRITE = 1;

int resolveVAddrExc(PCB* pcb, unsigned long vaddr, AddrExcKind kind, short rwx, SegDesc** ret) {
    unsigned long page = vaddr >> 14;
    SegDesc *sd;
    for (sd = pcb->segDesc; sd != NULL; sd = sd->next) {
        if (page >= sd->startingPage && page < sd->startingPage + sd->size) {
            break;
        }
    }
    if (sd == NULL) {
        return MEM_ACCESS_FAULT;
    }
    *ret = sd;
    switch (kind) {
        case pageFault:
            return LOAD_PAGE;
        case opDenied:
            if ((sd->rwx & rwx) == 0) {
                return MEM_ACCESS_FAULT;
            }
            return COPY_ON_WRITE;
        default:
            return MEM_ACCESS_FAULT;
    }
}
