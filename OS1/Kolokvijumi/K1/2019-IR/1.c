#include <stdlib.h>

typedef volatile unsigned int REG;
REG* ioCtrl = 1; // control register
REG* ioStatus = 2; // status register
REG* ioData = 3; // two data registers

typedef struct {
    REG* buffer; // Data buffer (block)
    unsigned int size; // Buffer (blok) size
    int status; // Status of operation
    IORequest* next; // Next in the list
} IORequest;

IORequest *ioHead;
const REG Start1 = 1;
const REG Start2 = 2;
const REG Ready1 = 1;
const REG Ready2 = 2;
const REG Error1 = 4;
const REG Error2 = 8;

void transfer() {
    if (ioHead != NULL) {
        return;
    }
    *ioCtrl |= (Start1 | Start2);
    while (ioHead != NULL) {
        unsigned int currBlock = 0;
        ioHead->status = 0;
        while (currBlock < ioHead->size) {
            int transferringTwo = (ioHead->size - currBlock) > 1;
            if ((*ioStatus & Ready1) != 0) {
                ioHead->buffer[currBlock++] = *ioData;
            }
            if ((*ioStatus & Error1) != 0) {
                ioHead->status = -1;
                ioHead = ioHead->next;
                break;
            }
            if (transferringTwo) {
                if ((*ioStatus & Ready2) != 0) {
                    ioHead->buffer[currBlock++] = *(ioData + 1);
                }
                if ((*ioStatus & Error2) != 0) {
                    ioHead->status = -1;
                    ioHead = ioHead->next;
                    break;
                }
            }
        }
        if (ioHead->status != -1) {
            ioHead = ioHead->next;
        }
    }
    *ioCtrl &= ~(Start1 | Start2);
}
