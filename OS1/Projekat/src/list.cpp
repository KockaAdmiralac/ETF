/**
 * list.cpp
 *
 * Implementation of a simple linked list.
 */
#include <kernel.h>
#include <list.h>
#include <stdlib.h>
#include <util.h>

/**
 * Constructs a new list.
 */
PtrList::PtrList() : back(nullptr), front(nullptr) {}

/**
 * Inserts an element into the list.
 * @param ptr Data to insert
 * @returns Whether the insertion succeeded
 */
int PtrList::insert(void* ptr) volatile {
    lockInterrupts("PtrList::insert");
    Element* element = new Element(ptr);
    if (element == nullptr) {
        unlockInterrupts("PtrList::insert (1)");
        return false;
    }
    if (back == nullptr) {
        back = element;
        front = element;
    } else {
        back->next = element;
        back = element;
    }
    unlockInterrupts("PtrList::insert (2)");
    return true;
}

/**
 * Removes an element from the list.
 * @returns The removed element, or null if empty
 */
void* PtrList::remove() volatile {
    if (front == nullptr) {
        return nullptr;
    }
    lockInterrupts("PtrList::remove");
    void* data = front->data;
    Element* oldFront = (Element*) front;
    front = front->next;
    delete oldFront;
    if (front == nullptr) {
        back = nullptr;
    }
    unlockInterrupts("PtrList::remove");
    return data;
}

/**
 * Deallocates all elements allocated by the list, but not the data associated.
 */
PtrList::~PtrList() {
    lockInterrupts("PtrList::~PtrList");
    Element* curr = (Element*) front;
    while (curr != nullptr) {
        Element* old = curr;
        curr = curr->next;
        delete old;
    }
    front = nullptr;
    back = nullptr;
    unlockInterrupts("PtrList::~PtrList");
}

/**
 * Initializes a new list element.
 * @param data Data to initialize the element with
 */
PtrList::Element::Element(void* data) : next(nullptr), data(data) {}

/**
 * Initializes a new empty result of PtrWaitingList#tick().
 */
PtrWaitingList::TickResult::TickResult() :
    data(nullptr), more(false) {}

/**
 * Initializes a new result of PtrWaitingList#tick().
 * @param data Data from the result
 * @param more Whether the method should be called again for more data
 */
PtrWaitingList::TickResult::TickResult(void* data, int more) :
    data(data), more(more) {}

/**
 * Constructs a new waiting list.
 */
PtrWaitingList::PtrWaitingList() :
    frontOrder(nullptr), backOrder(nullptr), frontTime(nullptr), size(0) {}

/**
 * Inserts a new element into the waiting list.
 * @param ptr Data to insert into the list
 * @param time Expiration time of the element, if set to zero the element does
 *             not expire
 * @returns Whether the insertion succeeded
 */
int PtrWaitingList::insert(void* ptr, unsigned time) volatile {
    lockInterrupts("PtrWaitingList::insert");
    checkListConsistency();
    Element* element = new Element(ptr, time);
    if (element == nullptr) {
        unlockInterrupts("PtrWaitingList::insert (1)");
        return false;
    }
    // Inserting by order.
    if (frontOrder == nullptr) {
        frontOrder = element;
        backOrder = element;
    } else {
        backOrder->nextOrder = element;
        element->prevOrder = (Element*) backOrder;
        backOrder = element;
    }
    // Inserting by time.
    if (time != 0) {
        if (frontTime == nullptr) {
            frontTime = element;
        } else {
            Element* curr = (Element*) frontTime;
            Element* prev = nullptr;
            do {
                // TODO: >= is perhaps unfair?
                if (curr->time >= element->time) {
                    element->nextTime = (Element*) curr;
                    curr->prevTime = element;
                    curr->time -= element->time;
                    if (prev == nullptr) {
                        // We're inserting in front of the first element.
                        frontTime = element;
                    } else {
                        prev->nextTime = element;
                        element->prevTime = prev;
                    }
                    break;
                } else {
                    element->time -= curr->time;
                }
                prev = curr;
                curr = curr->nextTime;
            } while (curr != nullptr);
            if (curr == nullptr) {
                prev->nextTime = element;
                element->prevTime = prev;
            }
        }
    }
    // Finished inserting.
    ++size;
    unlockInterrupts("PtrWaitingList::insert (2)");
    return true;
}

/**
 * Signals that one time unit has passed and returns an element if its waiting
 * time expired.
 * @returns The element whose waiting time expired and whether there are more
 *          results
 */
PtrWaitingList::TickResult PtrWaitingList::tick() volatile {
    if (frontTime == nullptr) {
        // Empty list.
        return TickResult();
    }
    lockInterrupts("PtrWaitingList::tick");
    checkListConsistency();
    if (frontTime->time != 0 && --frontTime->time != 0) {
        // Time hasn't expired.
        unlockInterrupts("PtrWaitingList::tick (1)");
        return TickResult();
    }
    void* data = frontTime->data;
    Element* oldFront = (Element*) frontTime;
    frontTime = frontTime->nextTime;
    frontTime->prevTime = nullptr;
    if (frontOrder == backOrder) {
        frontOrder = nullptr;
        backOrder = nullptr;
    } else if (frontOrder == oldFront) {
        frontOrder = frontOrder->nextOrder;
    } else if (backOrder == oldFront) {
        backOrder = backOrder->prevOrder;
    }
    if (oldFront->nextOrder != nullptr) {
        oldFront->nextOrder->prevOrder = oldFront->prevOrder;
    }
    if (oldFront->prevOrder != nullptr) {
        oldFront->prevOrder->nextOrder = oldFront->nextOrder;
    }
    delete oldFront;
    --size;
    unlockInterrupts("PtrWaitingList::tick (2)");
    return TickResult(data, frontTime != nullptr && frontTime->time <= 0);
}

/**
 * Removes an element from the waiting list in order that it was inserted in.
 * @returns The removed element, or null if empty
 */
void* PtrWaitingList::remove() volatile {
    if (frontOrder == nullptr) {
        return nullptr;
    }
    lockInterrupts("PtrWaitingList::remove");
    void* data = frontOrder->data;
    Element* oldFront = (Element*) frontOrder;
    checkListConsistency();
    frontOrder = frontOrder->nextOrder;
    frontOrder->prevOrder = nullptr;
    if (frontTime == oldFront) {
        frontTime = frontTime->nextTime;
        frontTime->prevTime = nullptr;
    }
    if (oldFront->nextTime != nullptr) {
        oldFront->nextTime->prevTime = oldFront->prevTime;
    }
    if (oldFront->prevTime != nullptr) {
        oldFront->prevTime->nextTime = oldFront->nextTime;
    }
    delete oldFront;
    if (frontOrder == nullptr) {
        backOrder = nullptr;
    }
    --size;
    unlockInterrupts("PtrWaitingList::remove");
    return data;
}

/**
 * Gets the amount of elements in the list. Useful for debugging.
 * @returns The amount of elements in the list
 */
unsigned PtrWaitingList::getSize() const volatile {
    return size;
}

/**
 * Deallocates all elements allocated by the list, but not the data associated.
 */
PtrWaitingList::~PtrWaitingList() {
    lockInterrupts("PtrWaitingList::~PtrWaitingList");
    Element* curr = (Element*) frontOrder;
    while (curr != nullptr) {
        Element* old = curr;
        curr = curr->nextOrder;
        delete old;
    }
    frontOrder = nullptr;
    backOrder = nullptr;
    frontTime = nullptr;
    unlockInterrupts("PtrWaitingList::~PtrWaitingList");
}

/**
 * Initializes a new waiting list element.
 * @param data Data to initialize the element with
 * @param time Time to initialize the element with
 */
PtrWaitingList::Element::Element(void* data, unsigned time) :
    nextOrder(nullptr), prevOrder(nullptr),
    nextTime(nullptr), prevTime(nullptr),
    data(data), time(time) {}

/**
 * Checks whether the list is consistent and exits the program if not.
 *
 * Only available during the debug mode! Assumes that interrupts have been
 * previously locked.
 */
void PtrWaitingList::checkListConsistency() volatile {
    #if KERNEL_DEBUG
    if (frontOrder != nullptr && frontOrder->prevOrder != nullptr) {
        syncPrint("frontOrder is not the first in order!\n");
        exit(1);
    }
    if (frontTime != nullptr && frontTime->prevTime != nullptr) {
        syncPrint("frontOrder is not the first in order!\n");
        exit(1);
    }
    if (backOrder != nullptr && backOrder->nextOrder != nullptr) {
        syncPrint("backOrder is not the last in order!\n");
        exit(1);
    }
    #endif
}
