typedef struct {
    long arr[10];
} InputStruct;

long foo(InputStruct s, long rdi) {
    if (rdi != 0) {
        return foo(s, rdi-1) * rdi;
    } else {
        return s.arr[0];
    }
}
