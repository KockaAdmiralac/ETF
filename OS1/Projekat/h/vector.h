/**
 * vector.h
 *
 * Naiive implementation of STL <vector>, with pointers as data type and thread
 * safety (as far as this kernel goes) in mind.
 */
#ifndef _VECTOR_H_
#define _VECTOR_H_

/**
 * Simple vector of pointers implementation.
 *
 * Maximum amount of pointers stored: 16383
 * Maximum index: 16382
 */
class PtrVector {
    public:
        PtrVector(unsigned initialCapacity = 256);
        int put(void* ptr) volatile;
        volatile void* get(unsigned index) const volatile;
        void remove(unsigned index) volatile;
        ~PtrVector();
        unsigned getCapacity() const volatile;
        unsigned getSize() const volatile;
        static const unsigned MAX_CAPACITY;
    private:
        // Cannot be copied. BC31 does not support deleting constructors.
        PtrVector(PtrVector&);
        PtrVector& operator=(PtrVector&);
        volatile void** data;
        volatile unsigned capacity;
        volatile unsigned size;
};

#endif
