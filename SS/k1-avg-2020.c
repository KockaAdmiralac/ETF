typedef union {
    long nizLong[7];
    int nizInt[14];
} StackUnion;

int foo(long* arg1, int arg2) {
    StackUnion unija;
    int niz1[4];
    niz1[3] = 0;
    while (niz1[3] <= 9) {
        unija.nizInt[niz1[3]] = arg2;
        niz1[3] += 1;
    }
    arg1[0] = unija.nizLong[0];
    arg1[1] = unija.nizLong[1];
    arg1[2] = unija.nizLong[2];
    arg1[3] = unija.nizLong[3];
    arg1[4] = unija.nizLong[4];
    return arg1;
}


/*
RA
BP              <-- RBP
RBX-  -  -  -  -<-- RBP - 0x08  -8
                <-- RBP - 0x10  -16
                <-- RBP - 0x18  -24
                <-- RBP - 0x20  -32
                <-- RBP - 0x28  -40
                <-- RBP - 0x30  -48
BBBBBBBBBBBBBBBB<-- RBP - 0x38  -56
                <-- RBP - 0x40  -64
00000000        <-- RBP - 0x48  -72
                <-- RBP - 0x50  -80
1111111111111111<-- RBP - 0x58  -88
22222222        <-- RBP - 0x60  -96



*/
