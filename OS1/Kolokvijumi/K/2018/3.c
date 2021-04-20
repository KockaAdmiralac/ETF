#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef int A;
typedef int B;
typedef int C;
typedef int D;
typedef void (*CallbackD)(D);
typedef struct {
    A a;
    B b;
    C c;
    CallbackD cb;
} Context;

int pthread_create(pthread_t *thread, void *(*routine)(void *), void *arg);
extern D fun (A a, B b, C c);

void fun_wrapper(void *arg) {
    Context *ctx = (Context *)arg;
    ctx->cb(fun(ctx->a, ctx->b, ctx->c));
    free(arg);
}

void fun_async(A a, B b, C c, CallbackD cb) {
    Context *ctx = malloc(sizeof(Context));
    ctx->a = a;
    ctx->b = b;
    ctx->c = c;
    ctx->cb = cb;
    pthread_t thread;
    pthread_create(&thread, fun_wrapper, ctx);
}
