#include <stdlib.h>

typedef unsigned long REG;
REG* ioCtrl =1; // control register
REG* ioStatus =2; // status register
REG* ioData =3; // data register
REG* ioBlock =4; // block address register
const unsigned int BLOCK_SIZE = 64;
const REG START_READING = 1;
const REG Ready = 1;
const REG Error = 2;

typedef struct {
    REG* buffer; // Data buffer (data block) in memory
    REG block; // The block number (address)
    int status; // Status of operation
    IORequest* next; // Next in the list
} IORequest;

IORequest *ioHead = NULL, *ioTail = NULL;

void doTransfer() {
    while (ioHead != NULL) {
        *ioBlock = ioHead->block;
        *ioCtrl = START_READING;
        while ((*ioStatus & (Ready | Error)) == 0);
        if ((*ioStatus & Error) != 0) {
            ioHead->status = -1;
            ioHead = ioHead->next;
            continue;
        }
        for (int i = 0; i < BLOCK_SIZE / sizeof(REG); ++i) {
            ioHead->buffer[i] = *ioData;
        }
        ioHead->status = 0;
        ioHead = ioHead->next;
    }
    ioTail = NULL;
}

void transfer(IORequest *request) {
    request->next = NULL;
    if (ioHead == NULL) {
        ioHead = request;
        ioTail = request;
        doTransfer();
    } else {
        ioTail->next = request;
        ioTail = ioTail->next;
    }
}
