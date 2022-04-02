#include "common.h"
int next = 0;
int tickets = 0;

void work();
void work2();

void worker() {
    while (true) {
        int ticket = tickets;
        while (!CAS(ticket, ticket+1, tickets)) skip();
        while (ticket != next) skip();
        work();
        next++;
        work2();
    }
}
