/**
 * list.h
 *
 * Naiive implementation of linked lists, with pointers as data type and thread
 * safety (as far as this kernel goes) in mind.
 */

/**
 * Simple linked list implementation.
 */
class PtrList {
    public:
        PtrList();
        int insert(void* ptr);
        void* remove();
        ~PtrList();
    private:
        struct Element {
            Element* next;
            void* data;
            Element(void* data);
        };
        // Cannot be copied. BC31 does not support deleting constructors.
        PtrList(PtrList&);
        PtrList& operator=(PtrList&);
        volatile Element* back;
        volatile Element* front;
};

/**
 * Implementation of a waiting list as a wrapper around a linked list.
 */
class PtrWaitingList {
    public:
        struct TickResult {
            void* data;
            int more;
            TickResult();
            TickResult(void* data, int more);
        };
        PtrWaitingList();
        int insert(void* ptr, unsigned time);
        TickResult tick();
        ~PtrWaitingList();
    private:
        struct Element {
            Element* next;
            void* data;
            unsigned time;
            Element(void* data, unsigned time);
        };
        // Cannot be copied. BC31 does not support deleting constructors.
        PtrWaitingList(PtrWaitingList&);
        PtrWaitingList& operator=(PtrWaitingList&);
        volatile Element* front;
};
