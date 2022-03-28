typedef struct {
    long array[16];
} InputStruct;

long foo(long arg1, long* arg2, InputStruct niz) {
    long var = niz.array[arg1];
    *arg2 += var;
    return var;
}
