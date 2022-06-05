#ifndef _CPU_HPP
#define _CPU_HPP
#include <cstdint>

struct CPU {
    static const uint16_t PSW_I = 0x8000;
    static const uint16_t PSW_Tl = 0x4000;
    static const uint16_t PSW_Tr = 0x2000;
    static const uint16_t PSW_N = 0x8;
    static const uint16_t PSW_C = 0x4;
    static const uint16_t PSW_O = 0x2;
    static const uint16_t PSW_Z = 0x1;
    int16_t registers[9] = {0};
    bool halted = false;
    bool zero();
    void zero(bool value);
    bool overflow();
    void overflow(bool value);
    bool carry();
    void carry(bool value);
    bool negative();
    void negative(bool value);
    bool timerMasked();
    void timerMasked(bool value);
    bool terminalMasked();
    void terminalMasked(bool value);
    bool interruptsMasked();
    void interruptsMasked(bool value);
};
#endif
