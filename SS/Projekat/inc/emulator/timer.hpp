#ifndef _TIMER_HPP
#define _TIMER_HPP
#include <chrono>
#include <cstdint>

struct Timer {
    uint16_t timCfg = 0;
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    bool interrupt = false;
    int64_t getInterval();
    void update();
};
#endif
