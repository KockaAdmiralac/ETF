typedef unsigned char byte;
typedef unsigned long ulong;
const byte BITS_IN_BYTE = 8;
const ulong NumOfBlocks = 64;
const ulong NumOfBytes = NumOfBlocks/BITS_IN_BYTE;

byte blocks[NumOfBytes];
void blockToBit(ulong blkNo, ulong& bt, byte& mask) {
    bt = blkNo/BITS_IN_BYTE;
    mask = 1<<(blkNo%BITS_IN_BYTE);
}
void bitToBlk(ulong& blkNo, ulong bt, byte mask) {
    blkNo = bt*BITS_IN_BYTE;
    for (; !(mask&1); mask>>=1) blkNo++;
}
ulong allocateBlock (ulong startingFrom) {
    ulong bt = 0;
    byte msk = 0;
    ulong blk1 = 0, blk2 = 0;
    for (ulong blk = startingFrom; blk<NumOfBlocks; blk++) {
        blockToBit(blk,bt,msk);
        if ((blocks[bt]&msk)==0) {
            blocks[bt] |= msk;
            blk1 = blk;
            break;
        }
    }
    for (ulong blk =1; blk<startingFrom; blk++) {
        blockToBit(blk,bt,msk);
        if ((blocks[bt]&msk)==0) {
            blocks[bt] |= msk;
            blk2 = blk;
            break;
        }
    }
    if (blk1 == 0) {
        return blk2;
    } else if (blk2 == 0) {
        return blk1;
    } else if (blk1 - startingFrom < startingFrom - blk2) {
        return blk1;
    } else {
        return blk2;
    }
}
