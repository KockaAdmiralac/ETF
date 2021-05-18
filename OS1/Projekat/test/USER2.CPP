/**
 * USER2.CPP
 *
 * Unit tests for various components that can be easily unit tested, such as
 * lists, vectors and other utilities.
 */
#include <kernel.h>
#include <list.h>
#include <stdlib.h>
#include <test.h>
#include <time.h>
#include <util.h>
#include <vector.h>

void testEnsure() {
    syncPrint("Testing ensure():\n");
    testCase("1. Test with true value", !ensure(true, "This should not be printed."));
    testCase("2. Test with false value (assertion should fail)", ensure(false, "This should be printed."));
}

void testGetBit() {
    syncPrint("Testing getBit():\n");
    testCase("1. Test with zero bit", getBit(0, 3) == 0);
    testCase("2. Test with zero bit again", getBit(0xFF, 9) == 0);
    testCase("3. Test with one bit", getBit(0xFFFF, 3) == 1);
    testCase("4. Test with one bit again", getBit(0xFFFF, 9) == 1);
    testCase("5. Test with invalid bit (assertion should fail)", getBit(0, 16) == 0);
}

void testGetPSW() {
    syncPrint("Testing getPSW():\n");
    lock
    testCase("1. Test with I = 0", getBit(getPSW(), 9) == 0);
    unlock
    testCase("2. Test with I = 1", getBit(getPSW(), 9) == 1);
}

void testUtil() {
    syncPrint("===================================== util =====================================\n");
    testEnsure();
    testGetBit();
    testGetPSW();
}

void testListDestructor() {
    PtrList l;
    int data1 = 1;
    int data2 = 2;
    testCase("Removing from empty list returns null", l.remove() == nullptr);
    testCase("Inserting first element into the list", l.insert(&data1));
    testCase("Inserting next element into the list", l.insert(&data2));
    testCase("Removing first element returns it", l.remove() == &data1);
    testCase("Inserting element after removal", l.insert(&data1));
    testCase("Removing second element returns it", l.remove() == &data2);
    testCase("Removing last element returns it", l.remove() == &data1);
    testCase("Removing again after last element returns null", l.remove() == nullptr);
    testCase("Inserting after removal of last element", l.insert(&data1));
    syncPrint("List destructor works... ");
}

void testWaitingListDestructor() {
    PtrWaitingList l;
    PtrWaitingList::TickResult tr;
    int data1 = 3;
    int data2 = 4;
    int data3 = 1025;
    tr = l.tick();
    // insert() + tick()
    testCase("Ticking from empty waiting list returns null", tr.data == nullptr && !tr.more);
    testCase("Inserting into empty waiting list", l.insert(&data1, 3));
    testCase("Inserting element after first", l.insert(&data1, 5));
    testCase("Inserting element in the middle of these two", l.insert(&data2, 4));
    tr = l.tick();
    testCase("Ticking first time slice returns nothing", tr.data == nullptr && !tr.more);
    testCase("Inserting element in front of the first", l.insert(&data2, 1));
    tr = l.tick();
    testCase("Ticking second time slice returns the just inserted element", tr.data == &data2 && !tr.more);
    testCase("Inserting element with same waiting time", l.insert(&data2, 2));
    tr = l.tick();
    testCase("Ticking third time returns the first inserted element", tr.data == &data1 && !tr.more);
    tr = l.tick();
    testCase("Ticking fourth time returns both the third", tr.data == &data2 && tr.more);
    tr = l.tick();
    testCase("and the fifth inserted element", tr.data == &data2 && !tr.more);
    tr = l.tick();
    testCase("Ticking fifth time returns the last element", tr.data == &data1 && !tr.more);
    tr = l.tick();
    testCase("Ticking sixth time returns nothing", tr.data == nullptr && !tr.more);
    testCase("Inserting back into empty waiting list works", l.insert(&data1, 2));
    tr = l.tick();
    testCase("Ticking seveth time returns nothing", tr.data == nullptr && !tr.more);
    tr = l.tick();
    testCase("Ticking eighth time returns the element", tr.data == &data1 && !tr.more);
    // insert() + remove()
    testCase("Removing from empty waiting list returns null", l.remove() == nullptr);
    testCase("Inserting first element into the waiting list", l.insert(&data1, 8));
    testCase("Inserting next element into the waiting list", l.insert(&data2, 4));
    testCase("Removing first element returns it regardless of waiting time", l.remove() == &data1);
    testCase("Inserting element after removal", l.insert(&data1, 8));
    testCase("Removing second element returns it regardless of waiting time", l.remove() == &data2);
    testCase("Removing last element returns it regardless of waiting time", l.remove() == &data1);
    testCase("Removing again after last element returns null", l.remove() == nullptr);
    // insert() + tick() + remove()
    testCase("Inserting after removal of last element", l.insert(&data1, 6));
    testCase("Removing from list of one element", l.remove() == &data1);
    tr = l.tick();
    testCase("Ticking from empty list should still return nothing", tr.data == nullptr && !tr.more);
    testCase("Reinserting after empty tick", l.insert(&data2, 3));
    testCase("Inserting to the beginning of time list but end of order list", l.insert(&data1, 2));
    testCase("Inserting element with infinite waiting time", l.insert(&data1, 0));
    testCase("Inserting to the end of both lists", l.insert(&data3, 4));
    testCase("Inserting element with same waiting time", l.insert(&data3, 3));
    tr = l.tick();
    testCase("First tick should return nothing", tr.data == nullptr && !tr.more);
    tr = l.tick();
    testCase("Second tick should return the second element by order", tr.data == &data1 && !tr.more);
    testCase("Removing should remove the first element by order", l.remove() == &data2);
    tr = l.tick();
    testCase("Third tick should return the fifth element by order", tr.data == &data3 && !tr.more);
    testCase("Removing should remove the third element by order", l.remove() == &data1);
    tr = l.tick();
    testCase("Fourth tick should remove the fourth element by order", tr.data == &data3 && !tr.more);
    tr = l.tick();
    testCase("Both ticking and removing should return nothing", l.remove() == nullptr && tr.data == nullptr && !tr.more);
    // Destructor
    syncPrint("Waiting list destructor works... ");
}

unsigned testListMemoryOveruse() {
    PtrList l;
    int data = 5;
    unsigned res = 0;
    while (true) {
        if (!l.insert(&data)) {
            break;
        }
        ++res;
    }
    for (unsigned i = 0; i < res; ++i) {
        if (l.remove() != &data) {
            return 0;
        }
    }
    if (l.remove() != nullptr) {
        return 0;
    }
    return res;
}

unsigned testWaitingListMemoryOveruse() {
    PtrWaitingList l;
    int data = 6;
    unsigned res = 0;
    while (true) {
        if (!l.insert(&data, 1)) {
            break;
        }
        ++res;
    }
    PtrWaitingList::TickResult tr;
    unsigned i = res;
    do {
        tr = l.tick();
        --i;
        if (tr.data != &data) {
            return 0;
        }
    } while (tr.more);
    if (i != 0) {
        return 0;
    }
    return res;
}

void testListMemoryLeak() {
    syncPrint("Testing memory leak... ");
    int data = 7;
    for (unsigned i = 0; i < 16; ++i) {
        PtrList l;
        for (unsigned j = 0; j < 16384; ++j) {
            if (!l.insert(&data)) {
                syncPrint("FAIL\n");
                return;
            }
        }
    }
    syncPrint("PASS\n");
}

void testWaitingListMemoryLeak() {
    syncPrint("Testing waiting list memory leak... ");
    int data = 8;
    for (unsigned i = 0; i < 16; ++i) {
        PtrWaitingList l;
        for (unsigned j = 0; j < 8192; ++j) {
            if (!l.insert(&data, 1)) {
                syncPrint("FAIL\n");
                return;
            }
        }
    }
    syncPrint("PASS\n");
}

void testWaitingListRandom() {
    syncPrint("Performing random testing... ");
    srand(time(nullptr));
    PtrWaitingList l;
    PtrWaitingList::TickResult tr;
    unsigned data = 53729U;
    unsigned elements = 0;
    for (unsigned i = 0; i < 65535U; ++i) {
        int number = rand() % 15;
        int ticks = rand() % 30;
        switch (number) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                if (l.insert(&data, ticks)) {
                    ++elements;
                } else {
                    syncPrint("Insertion failed at %d elements\n", elements);
                }
                break;
            case 8:
            case 9:
            case 10:
                if (l.remove() != nullptr) {
                    --elements;
                }
                break;
            case 11:
            case 12:
            case 13:
            case 14:
                for (unsigned i = 0; i < ticks; ++i) {
                    tr = l.tick();
                    while (tr.more) {
                        if (tr.data == nullptr) {
                            syncPrint("wtf\n");
                        }
                        --elements;
                        tr = l.tick();
                    }
                    if (tr.data != nullptr) {
                        --elements;
                    }
                }
                break;
        }
    }
    while (l.remove() == &data) {
        --elements;
    }
    if (elements == 0 && l.remove() == nullptr) {
        syncPrint("PASS\n");
    } else {
        syncPrint("FAIL\n");
    }
}

void testList() {
    syncPrint("===================================== list =====================================\n");
    testListDestructor();
    syncPrint("PASS\n");
    testWaitingListDestructor();
    syncPrint("PASS\n");
    syncPrint("Testing memory overuse... ");
    unsigned mor1 = testListMemoryOveruse();
    unsigned mor2 = testListMemoryOveruse();
    if (mor1 == mor2) {
        syncPrint("PASS (failed at index %u)\n", mor1);
    } else {
        syncPrint("FAIL\n");
    }
    syncPrint("Testing memory overuse for waiting list... ");
    mor1 = testWaitingListMemoryOveruse();
    mor2 = testWaitingListMemoryOveruse();
    if (mor1 == mor2) {
        syncPrint("PASS (failed at index %u)\n", mor1);
    } else {
        syncPrint("FAIL\n");
    }
    testListMemoryLeak();
    testWaitingListMemoryLeak();
    testWaitingListRandom();
}

void testVectorDestructor() {
    // Testing constructors.
    PtrVector v1;
    testCase("Capacity of the vector should be 256 by default", v1.getCapacity() == 256);
    testCase("Size of the vector should be 0 by default... ", v1.getSize() == 0);
    PtrVector v2(1);
    testCase("Capacity of the vector should be the one specified", v2.getCapacity() == 1);
    PtrVector v3(0);
    testCase("Capacity of the vector should be 256 if invalid (assertion should fail)", v3.getCapacity() == 256);
    PtrVector v4(PtrVector::MAX_CAPACITY);
    testCase("Maximum capacity should be 16383", v4.getCapacity() == 16383);
    // Testing put().
    int data1 = 1;
    int data2 = 2;
    testCase("The method should return new element index", v1.put(&data1) == 0);
    testCase("Capacity of the vector should not expand if large enough", v1.getCapacity() == 256);
    testCase("Size of the vector should be 1", v1.getSize() == 1);
    testCase("The data on index 0 should be correct", v1.get(0) == &data1);
    testCase("Inserting element at almost full capacity should work", v2.put(&data1) == 0);
    testCase("Capacity should remain unchanged if equal to size", v2.getCapacity() == 1);
    testCase("Inserting element at full capacity should work", v2.put(&data2) == 1);
    testCase("Capacity should increase if insufficient", v2.getCapacity() == 2);
    testCase("Element should be correct even if size increased", v2.get(1) == &data2);
    testCase("Inserting element at full capacity again should work", v2.put(&data1) == 2);
    testCase("Capacity should double if insufficient", v2.getCapacity() == 4);
    testCase("Size should properly update after capacity update", v2.getSize() == 3);
    testCase("Memory should be copied over after capacity update", v2.get(0) == &data1 && v2.get(1) == &data2);
    testCase("Inserting at max capacity but smaller size should work", v4.put(&data1) == 0);
    // Testing get().
    testCase("Getting an element out of size bounds should return null", v3.get(2) == nullptr);
    testCase("Getting an element out of capacity bounds should return null", v3.get(257) == nullptr);
    // Testing remove().
    v2.remove(3);
    testCase("Removing an element out of bound should not do anything", v2.get(0) == &data1 && v2.get(1) == &data2 && v2.get(2) == &data1);
    v2.remove(0);
    testCase("Removing an element from the beginning should not reduce its size", v2.getSize() == 3);
    testCase("The removed element should be null", v2.get(0) == nullptr);
    v2.remove(2);
    testCase("Removing an element from the end should reduce its size", v2.getSize() == 2);
    testCase("The removed element should be null", v2.get(2) == nullptr);
    v2.remove(1);
    testCase("Removing an element in front of a removed element should compact the vector", v2.getSize() == 0);
    // Testing destructor.
    syncPrint("Destructor for each of the vectors should work... ");
}

void testVectorFullCapacity() {
    PtrVector v(3);
    int data = 612;
    unsigned i = 0;
    syncPrint("Test filling the vector to full capacity... ");
    for (; i < 16383; ++i) {
        if (v.put(&data) != i) {
            syncPrint("FAIL (at index %d)\n", i);
            return;
        }
    }
    syncPrint("PASS\n");
    testCase("Capacity should be full", v.getCapacity() == PtrVector::MAX_CAPACITY);
    testCase("Capacity should be equal to size", v.getSize() == v.getCapacity());
    testCase("Attempting to insert a new element should fail (assertion should fail)", v.put(&data) == -1);
    syncPrint("All the data should remain in its place... ");
    for (i = 0; i < 16383; ++i) {
        if (v.get(i) != &data) {
            syncPrint("FAIL (at index %d)\n", i);
            return;
        }
    }
    syncPrint("PASS\n");
}

struct MemoryOveruseResult {
    unsigned vector;
    unsigned index;
    int failed;
    MemoryOveruseResult(unsigned vector, unsigned index, int failed = true) {
        this->vector = vector;
        this->index = index;
        this->failed = failed;
    }
};

int operator==(MemoryOveruseResult& mor1, MemoryOveruseResult& mor2) {
    return mor1.vector == mor2.vector &&
           mor1.index == mor2.index &&
           mor1.failed == mor2.failed;
}


MemoryOveruseResult testVectorMemoryOveruse() {
    PtrVector vectors[256];
    int data = 413;
    for (unsigned i = 0; i < 256; ++i) {
        for (unsigned j = 0; j < PtrVector::MAX_CAPACITY; ++j) {
            int dataIndex = vectors[i].put(&data);
            if (dataIndex == -2) {
                return MemoryOveruseResult(i, j);
            } else if (dataIndex != j) {
                return MemoryOveruseResult(i, j, false);
            }
        }
    }
    return MemoryOveruseResult(0, 0, false);
}

void testVectorMemoryLeak() {
    int data = 1405;
    syncPrint("Testing whether the vector leaks memory... ");
    for (unsigned i = 0; i < 65535U; ++i) {
        PtrVector v(PtrVector::MAX_CAPACITY);
        if (v.put(&data) < 0) {
            syncPrint("FAIL\n");
            return;
        }
    }
    syncPrint("PASS\n");
}

void testVector() {
    syncPrint("==================================== vector ====================================\n");
    testVectorDestructor();
    syncPrint("PASS\n");
    testVectorFullCapacity();
    syncPrint("Testing memory overuse...\n");
    MemoryOveruseResult mor1 = testVectorMemoryOveruse();
    MemoryOveruseResult mor2 = testVectorMemoryOveruse();
    if (mor1 == mor2) {
        syncPrint("PASS\nMemory overuse result: ");
        if (mor1.failed) {
            syncPrint("failed at vector %u and index %u\n", mor1.vector, mor1.index);
        } else {
            syncPrint("did not fail!\n");
        }
    } else {
        syncPrint("FAIL\n");
    }
    testVectorMemoryLeak();
}

void tick() {}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    testCase("Kernel can interrupt at the beginning of tests", Kernel::cannotInterrupt == 0);
    testUtil();
    testVector();
    testList();
    return 0;
}
