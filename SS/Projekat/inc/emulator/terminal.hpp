#ifndef _TERMINAL_HPP
#define _TERMINAL_HPP
#include <cstdint>
#include <termios.h>

struct Terminal {
    uint16_t termIn;
    bool interrupt;
    termios t;
    tcflag_t oldFlags;
    Terminal();
    void update();
    void write(uint16_t data);
    ~Terminal();
};
#endif
