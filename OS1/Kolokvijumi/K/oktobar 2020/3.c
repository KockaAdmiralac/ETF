#include <stdlib.h>

typedef unsigned int REG;
REG* dmaCtrl = 1; // DMA control register
REG* dmaStatus = 2; // DMA status register
REG* dmaAddress = 3; // DMA block address register
REG* dmaCount = 64; // DMA block size register

const REG Start = 1;
const REG TransferComplete = 1;
const REG Error = 2;
typedef struct IORequest {
    REG* buffer; // Data buffer (block)
    unsigned int size; // Buffer (blok) size
    int status; // Status of operation
    IORequest* next; // Next in the list
} IORequest;

IORequest *ioHead = NULL;
unsigned int blockCount = 0;

void transfer() {
    if (ioHead == NULL) {
        *dmaCtrl &= ~Start;
        return;
    }
    blockCount = 0;
    *dmaCtrl |= Start;
}
void dmaInterrupt() {
    if (ioHead == NULL) {
        return;
    }
    if ((*dmaStatus & Error) != 0) {
        ioHead->status = -1;
        ioHead = ioHead->next;
        transfer();
        return;
    }
    if ((*dmaStatus & TransferComplete) == 0) {
        return;
    }
    ioHead->buffer[blockCount++] = *dmaAddress;
    if (blockCount == ioHead->size) {
        ioHead->status = 0;
        ioHead = ioHead->next;
        transfer();
    }
}
