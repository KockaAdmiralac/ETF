/**
 * USER104.cpp
 *
 * Tests assigning different time slices and stack sizes to threads.
 * @see https://drive.google.com/open?id=11uyCIaCpMwSKIyfH7PFRzwGazAMxSnMa
 */
#include <thread.h>
#include <util.h>

volatile Time ts;

void tick() {
    syncPrint("timeSlice=%d\n", ts);
}

class TestThread : public Thread {
    public:
        TestThread(StackSize stackSize, Time timeSlice) :
            Thread(stackSize, timeSlice), myTimeSlice(timeSlice) {}
        ~TestThread() {
            waitToComplete();
        }
    protected:
        void run();
    private:
        Time myTimeSlice;
};

void TestThread::run() {
    for (unsigned i = 0; i < 32000; i++) {
        for (unsigned int j = 0; j < 32000; j++) {
            ts = myTimeSlice;
        }
    }
}

int userMain(int argc, char** argv) {
    (void) argc;
    (void) argv;
    syncPrint("Test starts.\n");
    TestThread t1(64, 1);
    TestThread t2(4096, 32);
    TestThread t3(1024, 16);
    TestThread t4(4096, 0);
    t1.start();
    t2.start();
    t3.start();
    t4.start();
    t1.waitToComplete();
    t2.waitToComplete();
    t3.waitToComplete();
    t4.waitToComplete();
    syncPrint("Test ends.\n");
    return 0;
}
