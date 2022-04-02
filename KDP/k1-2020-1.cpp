#include "common.h"

Node* tail = nullptr;

void worker() {
    while (true) {
        Node* node = new Node();
        node->locked = true;
        Node* prev = node;
        SWAP(prev, tail);
        while (prev != nullptr && prev->locked) skip();
        // Критична секција
        node->locked = false;
        // Некритична секција
    }
}
