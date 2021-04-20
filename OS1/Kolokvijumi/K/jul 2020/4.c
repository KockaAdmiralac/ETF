#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

unsigned int sleep(unsigned int sleep_time_in_seconds);
int close (int fd);
int write (int fd, const void *buffer, size_t size);
int open(const char *pathname, int flags, mode_t mode);

int send(const void *buffer, size_t size) {
    int fd;
    do {
        fd = open("../buffer.bin", O_WRONLY | O_CREAT | O_EXCL, S_IRWXU | S_IRWXG | S_IRWXO);
        if (fd == -1) {
            if (errno != EEXIST) {
                return -1;
            }
            sleep(5000);
        }
    } while (fd == -1);
    if (write(fd, buffer, size) < 0 || close(fd) < 0) {
        return -1;
    }
    return 0;
}
