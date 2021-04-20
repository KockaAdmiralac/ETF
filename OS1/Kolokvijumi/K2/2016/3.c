#include <stdlib.h>

void dealloc_pmt(unsigned* pmt);

int isEmptyPMT2(unsigned* pmt2) {
    // for ...
    return 0;
}

void releasePMTEntry (unsigned* pmt1, unsigned long page) {
    unsigned page1 = page >> 25;
    unsigned page2 = page & ((1 << 25) - 1);
    unsigned* pmt2 = ((unsigned*)(pmt1[page1] << 26));
    if (pmt2 == NULL || pmt2[page2] == 0) {
        return;
    }
    pmt2[page2] = 0;
    if (isEmptyPMT2(pmt2)) {
        dealloc_pmt(pmt2);
        pmt1[page1] = 0;
    }
}
