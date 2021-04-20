/**
 * t_vector.cpp
 *
 * Test module for vectors.
 * Does NOT test for critical section interruptions.
 */
#include <test.h>
#include <util.h>
#include <vector.h>

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
    cout << "Destructor for each of the vectors should work... ";
}

void testVectorFullCapacity() {
    PtrVector v(3);
    int data = 612;
    unsigned i = 0;
    cout << "Test filling the vector to full capacity... ";
    for (; i < 16383; ++i) {
        if (v.put(&data) != i) {
            cout << "FAIL (at index " << i << ")" << endl;
            return;
        }
    }
    cout << "PASS" << endl;
    testCase("Capacity should be full", v.getCapacity() == PtrVector::MAX_CAPACITY);
    testCase("Capacity should be equal to size", v.getSize() == v.getCapacity());
    testCase("Attempting to insert a new element should fail (assertion should fail)", v.put(&data) == -1);
    cout << "All the data should remain in its place... ";
    for (i = 0; i < 16383; ++i) {
        if (v.get(i) != &data) {
            cout << "FAIL (at index " << i << ")" << endl;
            return;
        }
    }
    cout << "PASS" << endl;
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

ostream& operator<<(ostream& os, MemoryOveruseResult& mor) {
    os << "Memory overuse result: ";
    if (mor.failed) {
        os << "failed at vector " << mor.vector << " and index " << mor.index;
    } else {
        os << "did not fail!";
    }
    return os;
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
    cout << "Testing whether the vector leaks memory... ";
    for (unsigned i = 0; i < 65535U; ++i) {
        PtrVector v(PtrVector::MAX_CAPACITY);
        if (v.put(&data) < 0) {
            cout << "FAIL" << endl;
            return;
        }
    }
    cout << "PASS" << endl;
}

void testVector() {
    cout << "==================================== vector ====================================" << endl;
    testVectorDestructor();
    cout << "PASS" << endl;
    testVectorFullCapacity();
    cout << "Testing memory overuse... " << endl;
    MemoryOveruseResult mor1 = testVectorMemoryOveruse();
    MemoryOveruseResult mor2 = testVectorMemoryOveruse();
    if (mor1 == mor2) {
        cout << "PASS" << endl << mor1 << endl;
    } else {
        cout << "FAIL" << endl;
    }
    testVectorMemoryLeak();
}
