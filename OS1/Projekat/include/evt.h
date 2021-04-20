/**
 * evt.h
 *
 * Interface for event listeners. Non-cosmetic changes are NOT ALLOWED.
 */
#ifndef _EVT_H_
#define _EVT_H_

typedef unsigned char IVTNo;

class KernelEv;

/**
 * An interface to kernel event listeners.
 */
class Event {
    public:
        Event(IVTNo ivtNo);
        ~Event();
        void wait();
    protected:
        friend class KernelEv;
        void signal();
    private:
        KernelEv* myImpl;
};

#endif
