/**
 * vector.cpp
 *
 * Implementation of a simple pointer vector.
 */
#include <kernel.h>
#include <string.h>
#include <util.h>
#include <vector.h>

/**
 * Maximum possible capacity of a vector.
 */
const unsigned PtrVector::MAX_CAPACITY = 0xFFFF / sizeof(void*);

/**
 * Constructs a new vector with a starting capacity.
 * @param initialCapacity Starting capacity of the vector
 */
PtrVector::PtrVector(unsigned initialCapacity) : size(0) {
    lockInterrupts("PtrVector::PtrVector");
    if (ensure(initialCapacity > 0, "Initial capacity cannot be 0!")) {
        initialCapacity = 256;
    }
    capacity = initialCapacity;
    data = new void*[capacity];
    if (ensure(data != nullptr, "Vector initial capacity failed to allocate!")) {
        // We shall retry creating the vector on every put().
        capacity = 0;
    }
    unlockInterrupts("PtrVector::PtrVector");
}

/**
 * Puts a pointer into the vector.
 *
 * Returns an error code if allocation fails. Error codes are:
 * -1: the vector is at maximum capacity
 * -2: memory allocation failed
 * @param ptr Pointer to put into the vector
 * @returns Index of the newly added element, or error code on failure
 */
int PtrVector::put(void* ptr) volatile {
    if (ensure(size < MAX_CAPACITY, "We are at maximum capacity!")) {
        return -1;
    }
    lockInterrupts("PtrVector::put");
    if (size == capacity) {
        unsigned newCapacity = (capacity == 0) ?
            1 :
            capacity * 2;
        if (newCapacity < capacity || newCapacity > MAX_CAPACITY) {
            // The capacity overflowed or we reached maximum capacity.
            newCapacity = MAX_CAPACITY;
        }
        void** newData = new void*[newCapacity];
        if (ensure(newData != nullptr, "Failed to allocate new vector data!")) {
            unlockInterrupts("PtrVector::put (1)");
            return -2;
        }
        memcpy(newData, data, size * sizeof(void*));
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    data[size++] = ptr;
    unlockInterrupts("PtrVector::put (2)");
    return size-1;
}

/**
 * Gets a pointer from the vector.
 * @param index Index of the pointer to get
 * @returns Pointer from the vector, or nullptr
 */
volatile void* PtrVector::get(unsigned index) const volatile {
    if (index >= size) {
        return nullptr;
    }
    return data[index];
}

/**
 * Removes a pointer from the vector and trivially compacts the vector if
 * possible.
 * @param index Index of the pointer to remove
 * @todo This can be more efficient!
 */
void PtrVector::remove(unsigned index) volatile {
    if (index >= size) {
        return;
    }
    lockInterrupts("PtrVector::remove");
    data[index] = nullptr;
    while (data[size-1] == nullptr && size > 0) {
        --size;
    }
    unlockInterrupts("PtrVector::remove");
}

/**
 * Deallocates all memory used by the vector and its pointers.
 *
 * Should be safe to call before actual vector destruction, but why would you?
 */
PtrVector::~PtrVector() {
    lockInterrupts("PtrVector::~PtrVector");
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    size = 0;
    capacity = 0;
    unlockInterrupts("PtrVector::~PtrVector");
}

/**
 * Gets the capacity of the vector.
 * @returns Capacity of the vector
 */
unsigned PtrVector::getCapacity() const volatile {
    return (unsigned) capacity;
}

/**
 * Gets the size of the vector.
 * @returns Size of the vector
 */
unsigned PtrVector::getSize() const volatile {
    return (unsigned) size;
}
