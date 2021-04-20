#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define N 100

int main(int argc, char **argv) {
    if (N <= 0) {
        return EXIT_SUCCESS;
    }
    pid_t pids[N];
    for (int i = 0; i < N; ++i) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork() failed\n");
            return EXIT_FAILURE;
        } else if (pids[i] == 0) {
            if (execlp(argv[1], argv[1]) < 0) {
                perror("execlp() failed\n");
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }
    }
    int waited = wait(NULL, 5000);
    if (waited == 0) {
        return EXIT_SUCCESS;
    } else if (waited < 0) {
        perror("wait() failed\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < N; ++i) {
        waited = wait(pids[i], 0);
        if (waited > 0) {
            if (kill(pids[i]) < 0) {
                perror("kill() failed\n");
                return EXIT_FAILURE;
            }
        } else if (waited < 0) {
            perror("wait() failed\n");
            return EXIT_FAILURE;
        }
    }
    return 0;
}
