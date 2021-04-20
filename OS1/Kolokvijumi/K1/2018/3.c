#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

int main() {
    char cmd[33];
    while (true) {
        scanf("%32s", cmd);
        if (strcmp(cmd, "q") == 0) {
            break;
        }
        pid_t pid = fork();
        if (pid < 0) {
            printf("Kreiranje procesa nije uspelo.\n");
            continue;
        } else if (pid == 0) {
            execlp(cmd, cmd);
        } else {
            wait(pid);
        }
    }
    return 0;
}
