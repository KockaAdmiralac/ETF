#include <stdlib.h>
#include <stdbool.h>

unsigned long alloc_pmt2();
void* kaddrPtoV (void* physicalAddr);

void allocatePage(unsigned *pmt, unsigned long page, unsigned long frame, unsigned short rwx) {
    unsigned long pmt2Entry = *(pmt + (page >> 25) * 32);
    if (pmt2Entry == 0) {
        // Mapping not allowed
        return;
    } else if ((pmt2Entry << 6) == 0) {
        pmt2Entry = alloc_pmt2();
        *(pmt + (page >> 25) * 32) = pmt2Entry;
    }
    unsigned *pmt2 = kAddrPtoV(NULL + pmt2Entry * 16 * 1024);
    unsigned entry = (1 << 30) | (rwx << 27) | frame;
    *(pmt2 + (page & ((1 << 25) - 1))) = entry;
}

void initPMT(unsigned* pmt, unsigned long pageFrom, unsigned long nPages, unsigned long frameFrom, unsigned short rwx) {
    for (unsigned long i = 0; i < nPages; ++i) {
        allocatePage(pmt, pageFrom + i, frameFrom + i, rwx);
    }
}
