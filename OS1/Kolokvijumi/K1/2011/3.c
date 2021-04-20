void longjmp(jmp_buf buf, int value) {
    asm{
        load r0, -1*4[r0];
        store 0*4[r0], psw
        store 1*4[r0], r1
        store 2*4[r0], r2
        ...
        store 31*4[r0], r31
        store 32*4[r0], sp
        store 33*4[r0], r0
        push r0
        load r0, -2*4[r0]
    }
}
