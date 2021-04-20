#include <stdlib.h>

typedef unsigned int REG;
REG* ioCtrl = 1; // control register
REG* ioStatus = 2; // status register
REG* ioData = 3; // data register
const unsigned BlockSize = 64; // block size

typedef struct IORequest {
    REG* buffer; // Data buffer (block)
    int status; // Status of operation
    struct IORequest* next; // Next in the list
} IORequest;

const unsigned int Start = 1;
const unsigned int Ready = 1;
const unsigned int Error = 2;
IORequest *ioHead = NULL;
unsigned int currBlock = 0;

void transfer() {
    if (ioHead == NULL) {
        return;
    }
    *ioCtrl |= Start;
}
void ioInterrupt() {
    if (ioHead == NULL) {
        // WTF?
        return;
    }
    if ((*ioStatus & Error) != 0) {
        ioHead->status = -1;
        ioHead = ioHead->next;
        currBlock = 0;
        *ioCtrl &= ~Start;
        return;
    }
    if ((*ioStatus & Ready) == 0) {
        // ???
        return;
    }
    ioHead->buffer[currBlock] = *ioData;
    if (++currBlock == BlockSize) {
        ioHead->status = 0;
        ioHead = ioHead->next;
        currBlock = 0;
        *ioCtrl &= ~Start;
    }
    transfer();
}
