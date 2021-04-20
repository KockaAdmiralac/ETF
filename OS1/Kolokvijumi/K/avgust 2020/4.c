#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int write(int fd, const void *buffer, size_t size);
int open(const char *pathname, int flags, mode_t mode);

typedef struct node {
    int contents;
    struct node *left, *right;
} Node;

int inorder(int fd, Node *node) {
    int err;
    if (node->left != NULL) {
        err = inorder(fd, node->left);
        if (err < 0) {
            return err;
        }
    }
    char str[16];
    sprintf(str, "%d", node->contents);
    if (write(fd, str, 16) < 0) {
        return -2;
    }
    if (node->right != NULL) {
        err = inorder(fd, node->right);
        if (err < 0) {
            return err;
        }
    }
    return 0;
}

int save(const char* fname, Node* root) {
    int fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IROTH);
    if (fd < 0) {
        return -1;
    }
    int err;
    if (root != NULL) {
        err = inorder(fd, root);
        if (err < 0) {
            return err;
        }
    }
    if (close(fd) < 0) {
        return -3;
    }
    return 0;
}
