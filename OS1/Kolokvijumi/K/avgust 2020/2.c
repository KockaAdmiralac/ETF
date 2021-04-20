#include <stdlib.h>

typedef struct {
    SegDesc *segdesc;
} PCB;
typedef struct SegDesc {
    struct SegDesc *left, *right;
    size_t pg, sz;
    // ...
    // vtp
} SegDesc;

SegDesc* findSegDesc(SegDesc* root, size_t page) {
    SegDesc *curr = root;
    while (curr != NULL) {
        if (curr->pg <= page && curr->pg + curr->sz > page) {
            break;
        } else if (curr->pg > page) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return curr;
}

int loadPage(size_t page, size_t frame);
size_t allocateFrame();
void setPMTEntry(PCB* pcb, size_t page, size_t frame, SegDesc* sd);

int handlePageFault(PCB* pcb, size_t page) {
    SegDesc *sd = findSegDesc(pcb, page);
    if (sd == NULL) {
        // Segfault
        return -1;
    }
    size_t frame = allocateFrame();
    if (frame == 0) {
        // Failed to allocate frame
        return -2;
    }
    if (loadPage(page, frame) < 0) {
        // Failed to load page
        return -3;
    }
    setPMTEntry(pcb, page, frame, sd);
    return 0;
}
