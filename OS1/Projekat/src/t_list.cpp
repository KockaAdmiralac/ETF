/**
 * t_list.cpp
 *
 * Test module for lists.
 * Does NOT test critical section interruptions.
 */
#include <list.h>
#include <stdlib.h>
#include <test.h>
#include <time.h>
#include <util.h>

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
    cout << "List destructor works... ";
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
    cout << "Waiting list destructor works... ";
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
    cout << "Testing memory leak... ";
    int data = 7;
    for (unsigned i = 0; i < 16; ++i) {
        PtrList l;
        for (unsigned j = 0; j < 16384; ++j) {
            if (!l.insert(&data)) {
                cout << "FAIL" << endl;
                return;
            }
        }
    }
    cout << "PASS" << endl;
}

void testWaitingListMemoryLeak() {
    cout << "Testing waiting list memory leak... ";
    int data = 8;
    for (unsigned i = 0; i < 16; ++i) {
        PtrWaitingList l;
        for (unsigned j = 0; j < 16384; ++j) {
            if (!l.insert(&data, 1)) {
                cout << "FAIL" << endl;
                return;
            }
        }
    }
    cout << "PASS" << endl;
}

void testWaitingListRandom() {
    cout << "Performing random testing... ";
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
                // cout << "\r" << i << " insertion";
                if (l.insert(&data, ticks)) {
                    ++elements;
                } else {
                    cout << "Insertion failed at " << elements << " elements" << endl;
                }
                break;
            case 8:
            case 9:
            case 10:
                // cout << "\r" << i << " removal";
                if (l.remove() != nullptr) {
                    --elements;
                }
                break;
            case 11:
            case 12:
            case 13:
            case 14:
                // cout << "\r" << i << " ticking " << ticks;
                for (unsigned i = 0; i < ticks; ++i) {
                    tr = l.tick();
                    while (tr.more) {
                        if (tr.data == nullptr) {
                            cout << "wtf" << endl;
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
        cout << "PASS" << endl;
    } else {
        cout << "FAIL" << endl;
    }
}

void testList() {
    cout << "===================================== list =====================================" << endl;
    testListDestructor();
    cout << "PASS" << endl;
    testWaitingListDestructor();
    cout << "PASS" << endl;
    cout << "Testing memory overuse... ";
    unsigned mor1 = testListMemoryOveruse();
    unsigned mor2 = testListMemoryOveruse();
    if (mor1 == mor2) {
        cout << "PASS (failed at index " << mor1 << ")" << endl;
    } else {
        cout << "FAIL" << endl;
    }
    cout << "Testing memory overuse for waiting list... ";
    mor1 = testWaitingListMemoryOveruse();
    mor2 = testWaitingListMemoryOveruse();
    if (mor1 == mor2) {
        cout << "PASS (failed at index " << mor1 << ")" << endl;
    } else {
        cout << "FAIL" << endl;
    }
    testListMemoryLeak();
    testWaitingListMemoryLeak();
    testWaitingListRandom();
}
