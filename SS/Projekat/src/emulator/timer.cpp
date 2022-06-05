#include <stdexcept>
#include "emulator/timer.hpp"

int64_t Timer::getInterval() {
    switch (timCfg % 8) {
        case 0: return 500;
        case 1: return 1000;
        case 2: return 1500;
        case 3: return 2000;
        case 4: return 5000;
        case 5: return 10000;
        case 6: return 30000;
        case 7: return 60000;
    }
    throw std::runtime_error("Timer configuration invalid [this should never happen].");
}

void Timer::update() {
    auto now = std::chrono::steady_clock::now();
    auto passed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime);
    if (passed.count() >= getInterval()) {
        interrupt = true;
        lastTime = now;
    }
}
