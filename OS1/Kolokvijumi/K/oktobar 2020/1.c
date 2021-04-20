#include <stdlib.h>

int spawnvp (int mode, char *path, const char **argv);

int multispawn (int number, const char* path, const char* args[]) {
    int num = 0;
    for (int i = 0; i < number; ++i) {
        const char *argv[] = {path, argv[i], NULL};
        if (spawnvp(P_NOWAIT, path, argv) == 0) {
            ++num;
        }
    }
    return num;
}
