void fread (FHANDLE, int position, double* buffer, int bufferSize);
void fwrite(FHANDLE, int position, double* buffer, int bufferSize);

class DLArray {
public:
    inline DLArray (int size, int blockSize, FHANDLE fromFile);
    inline double get (int i); // Get element [i]
    inline void set (int i, double x); // Set element [i]
protected:
    inline void save(int slot);
    inline void load(int blockNo);
    inline void fetch(int blockNo);
private:
    FHANDLE file;
    int size, blockSize;
    int curBlock[2];
    int dirty[2];
    double* block[2];
};
DLArray::DLArray (int s, int bs, FHANDLE f) :
    file(f), size(s), blockSize(bs), curBlock({0, 1}), dirty({0, 0}) {
    block[0] = new double[bs];
    block[1] = new double[bs];
    if (block[0]) load(curBlock[0]);
    if (block[1]) load(curBlock[1]);
}
void DLArray::save(int slot) {
    fwrite(file, curBlock[slot] * blockSize, block[slot], blockSize);
    dirty[slot] = 0;
}
void DLArray::load(int b) {
    int slot = b % 2;
    curBlock[slot] = b;
    fread(file, curBlock[slot] * blockSize, block[slot], blockSize);
    dirty[slot] = 0;
}
void DLArray::fetch(int b) {
    int slot = b % 2;
    if (curBlock[slot] != b) {
        if (dirty[slot]) save(slot);
        load(b);
    }
}
double DLArray::get(int i) {
    int b = i/blockSize;
    int slot = b % 2;
    if (block[slot]==0 || i<0 || i>=size) return 0; // Exception
    fetch(b);
    return block[slot][i%blockSize];
}
void DLArray::set (int i, double x) {
    int b = i/blockSize;
    int slot = b % 2;
    if (block[slot]==0 || i<0 || i>=size) return; // Exception
    fetch(b);
    if (block[slot][i%blockSize]!=x) {
        block[slot][i%blockSize]=x;
        dirty[slot]=1;
    }
}
