/**
 * list.cpp
 *
 * Implementation of a simple linked list.
 */
#include <kernel.h>
#include <list.h>
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
int PtrList::insert(void* ptr) {
    lockInterrupts
    Element* element = new Element(ptr);
    if (element == nullptr) {
        unlockInterrupts
        return false;
    }
    if (back == nullptr) {
        back = element;
        front = element;
    } else {
        back->next = element;
        back = element;
    }
    unlockInterrupts
    return true;
}

/**
 * Removes an element from the list.
 * @returns The removed element, or null if empty
 */
void* PtrList::remove() {
    if (front == nullptr) {
        return nullptr;
    }
    void* data = front->data;
    Element* oldFront = (Element*) front;
    lockInterrupts
    front = front->next;
    delete oldFront;
    if (front == nullptr) {
        back = nullptr;
    }
    unlockInterrupts
    return data;
}

/**
 * Deallocates all elements allocated by the list, but not the data associated.
 */
PtrList::~PtrList() {
    lockInterrupts
    Element* curr = (Element*) front;
    while (curr != nullptr) {
        Element* old = curr;
        curr = curr->next;
        delete old;
    }
    unlockInterrupts
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
PtrWaitingList::PtrWaitingList() : front(nullptr) {}

/**
 * Inserts a new element into the waiting list.
 * @param ptr Data to insert into the list
 * @param time Non-zero wait time of the element
 * @returns Whether the insertion succeeded
 */
int PtrWaitingList::insert(void* ptr, unsigned time) {
    if (time == 0) {
        // There's nothing to wait for here.
        return false;
    }
    lockInterrupts
    Element* element = new Element(ptr, time);
    if (element == nullptr) {
        unlockInterrupts
        return false;
    }
    if (front == nullptr) {
        front = element;
    } else {
        Element* curr = (Element*) front;
        Element* prev = nullptr;
        do {
            // TODO: >= is perhaps unfair?
            if (curr->time >= element->time) {
                element->next = (Element*) curr;
                curr->time -= element->time;
                if (prev == nullptr) {
                    // We're inserting in front of the first element.
                    front = element;
                } else {
                    prev->next = element;
                }
                break;
            } else {
                element->time -= curr->time;
            }
            prev = curr;
            curr = curr->next;
        } while (curr != nullptr);
        if (curr == nullptr) {
            prev->next = element;
        }
    }
    unlockInterrupts
    return true;
}

/**
 * Signals that one time unit has passed and returns an element if its waiting
 * time expired.
 * @returns The element whose waiting time expired and whether there are more
 *          results
 */
PtrWaitingList::TickResult PtrWaitingList::tick() {
    if (front == nullptr) {
        // Empty list.
        return TickResult();
    }
    lockInterrupts
    if (front->time != 0 && --front->time != 0) {
        // Time hasn't expired.
        unlockInterrupts
        return TickResult();
    }
    void* data = front->data;
    Element* oldFront = (Element*) front;
    front = front->next;
    delete oldFront;
    unlockInterrupts
    return TickResult(data, front != nullptr && front->time == 0);
}

/**
 * Deallocates all elements allocated by the list, but not the data associated.
 *
 * Same code as PtrList::~PtrList().
 */
PtrWaitingList::~PtrWaitingList() {
    lockInterrupts
    Element* curr = (Element*) front;
    while (curr != nullptr) {
        Element* old = curr;
        curr = curr->next;
        delete old;
    }
    unlockInterrupts
}

/**
 * Initializes a new waiting list element.
 * @param data Data to initialize the element with
 * @param time Time to initialize the element with
 */
PtrWaitingList::Element::Element(void* data, unsigned time) :
    next(nullptr), data(data), time(time) {}
