#include <dos.h>
#include <iostream.h>
#include <schedule.h>
#include <util.h>

#define lock asm cli
#define unlock asm sti

struct PCB {
    unsigned bp;
    unsigned sp;
    unsigned ss;
    unsigned finished;
    int timeSlice;
};

PCB* allPCBs[3];
volatile PCB* running;

unsigned tsp;
unsigned tss;
unsigned tbp;

volatile int counter = 20;
volatile int contextSwitchOnDemand = 0;
volatile unsigned lockFlag = 1;

// interrupt - push psw, push pc, push all eight registers
// interrupt bit is only cleared if entering from an interrupt
// asynchronous - timer took away the thread
// synchronous - explicitly calling timer()
void interrupt timer(...) {
    if (!contextSwitchOnDemand) {
        --counter;
    }
    if (counter == 0 || contextSwitchOnDemand) {
        if (lockFlag) {
            contextSwitchOnDemand = 0;
            asm {
                mov tsp, sp
                mov tss, ss
                mov tbp, bp
            }
            running->sp = tsp;
            running->ss = tss;
            running->bp = tbp;
            if (!running->finished) {
                Scheduler::put((PCB*) running);
            }
            // cout MOŽDA postavlja I bit, radite lock ako ste unutar funkcije koja očekuje da je isključen i ako ste SIGURNI da je isključen
            // Scheduler::get vraća 0 ako nema niti
            running = Scheduler::get();
            tsp = running->sp;
            tss = running->ss;
            tbp = running->bp;
            counter = running->timeSlice;
            asm {
                mov sp, tsp
                mov ss, tss
                mov bp, tbp
            }
        } else {
            contextSwitchOnDemand = 1;
        }
    }
    if (!contextSwitchOnDemand) {
        // Old timer interrupt routine should be called
        asm int 60h;
    }
    // contextSwitchOnDemand = 0;
}

void interrupt wtf(...) {
    cout << "We called an interrupt" << endl;
    // oldTimerRoutine();
}

void dispatch() {
    lock
    contextSwitchOnDemand = 1;
    timer();
    unlock
}

// postavlja novu prekidnu rutinu
void initialize() {
    lock
    setvect(0x60, getvect(0x08));
    setvect(0x08, timer);
    unlock
}

// vraca staru prekidnu rutinu
void restore() {
    lock
    setvect(0x08, getvect(0x60));
    unlock
}


void exitThread() {
    running->finished = 1;
    dispatch();
}

void a() {
    for (int i = 0; i < 30; ++i) {
        lockFlag = 0;
        cout << "u a() i = " << i << " " << (getPSW() & 0x200) << endl;
        lockFlag = 1;
        if (contextSwitchOnDemand) {
            dispatch();
        }
        // asm int 61h;
        for (int k = 0; k < 100; ++k) {
            for (int j = 0; j < 3000; ++j);
        }
    }
    exitThread();
}

void b() {
    for (int i = 0; i < 30; ++i) {
        lockFlag = 0;
        cout << "u b() i = " << i << " " << (getPSW() & 0x200) << endl;
        lockFlag = 1;
        if (contextSwitchOnDemand) {
            dispatch();
        }
        for (int k = 0; k < 100; ++k) {
            for (int j = 0; j < 3000; ++j);
        }
    }
    exitThread();
}

// 1023 - PSW
// 1022 - PC (SEG)
// 1021 - PC (OFF)
// 1020 - REG 1
// 1019 - REG 2
// 1018 - REG 3
// 1017 - REG 4
// 1016 - REG 5
// 1015 - REG 6
// 1014 - REG 7
// 1013 - REG 8
// 1012 <- SP
// Address - 20b
void createProcess(PCB* newPCB, void (*body)()) {
    unsigned* stack1 = new unsigned[1024];
    stack1[1023] = 0x200; // PSW, I = 1
    stack1[1022] = FP_SEG(body);
    stack1[1021] = FP_OFF(body);
    newPCB->sp = FP_OFF(stack1 + 1012); // Leaving enough place for saved registers
    newPCB->ss = FP_SEG(stack1 + 1012);
    newPCB->bp = newPCB->sp;
    newPCB->finished = 0;
    Scheduler::put((PCB*) newPCB);
}

void doSomething() {
    lock
    allPCBs[1] = new PCB();
    createProcess(allPCBs[1], a);
    cout << "napravio a" << endl;
    allPCBs[1]->timeSlice = 40;

    allPCBs[2] = new PCB();
    createProcess(allPCBs[2], b);
    cout << "napravio b" << endl;
    allPCBs[2]->timeSlice = 20;

    allPCBs[0] = new PCB();
    running = allPCBs[0];
    running->finished = 0;
    unlock

    while (!(allPCBs[1]->finished && allPCBs[2]->finished)) {
        lock
        cout << "main() " << getBit(getPSW(), 9) << endl;
        unlock
        dispatch();
    }
    running->finished = 1;
    cout << "Done." << endl;
}

int main() {
    initialize();
    doSomething();
    restore();
    return 0;
}
