#include <stdlib.h>
#include <math.h>

const size_t PAGE_SZ = 1024;
const size_t PAGE_OFFS_SZ = 10;

typedef struct SegDesc {
    struct SegDesc *prev, *next;
    size_t pg, sz;
} SegDesc;

int insert_seg_desc (SegDesc* sd, size_t pg, size_t sz) {
    SegDesc* nsd = alloc_seg_desc();
    if (!nsd) return -1; // Error: cannot allocate SegDesc
    nsd->pg = pg; nsd->sz = sz;
    nsd->next = sd->next; nsd->prev = sd;
    sd->next->prev = nsd; sd->next = nsd;
    return 0;
}

void* vmalloc (SegDesc* head, void* addr, size_t size) {
    size_t pgSize = ceil(size/PAGE_SZ);
    if (addr == NULL) {
        //
    } else {
        //
    }
}
