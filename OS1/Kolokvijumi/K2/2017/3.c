#include <stdlib.h>

unsigned long alloc_pmt();
typedef enum {
    UNALLOCATED,
    EXECUTE,
    READ,
    READWRITE
} AccessMode;

int sharePage(unsigned* pmtFrom, unsigned long pageFrom, unsigned* pmtTo, unsigned long pageTo) {
    if (pmtFrom == NULL || pmtTo == NULL) {
        return -1;
    }
    unsigned pmtFrom1Entry = *(pmtFrom + (pageFrom >> 25));
    unsigned pmtTo1Entry = *(pmtTo + (pageTo >> 25));
    if (pmtFrom1Entry == 0) {
        return -1;
    }
    if (pmtTo1Entry == 0) {
        pmtTo1Entry = alloc_pmt();
        *(pmtTo + (pageTo >> 25)) = pmtTo1Entry;
    }
    unsigned *pmtFrom2 = NULL + pmtFrom1Entry * 16 * 1024;
    unsigned *pmtTo2 = NULL + pmtTo1Entry * 16 * 1024;
    unsigned pmtFrom2Entry = *(pmtFrom2 + (pageFrom & (1 << 25) - 1));
    *(pmtTo2 + (pageTo & (1 << 25) - 1)) = pmtFrom2Entry;
}
