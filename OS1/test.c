#include <unistd.h>
#include <stdio.h>

int main(void) {
    printf("%ld\n", sysconf(_SC_PAGESIZE));
    return 0;
}
