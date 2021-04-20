/**
 * vector.h
 *
 * Naiive implementation of STL <vector>, with pointers as data type and thread
 * safety (as far as this kernel goes) in mind.
 */

/**
 * Simple vector of pointers implementation.
 *
 * Maximum amount of pointers stored: 16383
 * Maximum index: 16382
 */
class PtrVector {
    public:
        PtrVector(unsigned initialCapacity = 256);
        int put(void* ptr);
        volatile void* get(unsigned index) const;
        void remove(unsigned index);
        ~PtrVector();
        unsigned getCapacity() const;
        unsigned getSize() const;
        static const unsigned MAX_CAPACITY;
    private:
        // Cannot be copied. BC31 does not support deleting constructors.
        PtrVector(PtrVector&);
        PtrVector& operator=(PtrVector&);
        volatile void** data;
        volatile unsigned capacity;
        volatile unsigned size;
};
