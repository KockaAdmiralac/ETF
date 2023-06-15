#include <timer.hpp>
#include <iostream>

std::unordered_map<std::string, std::stack<TimePoint>> Timer::events;
std::unordered_map<std::string, std::vector<Measurement>> Timer::measurements;

void Timer::start(const std::string& event) {
    events[event].push(std::chrono::steady_clock::now());
}

void Timer::end(const std::string& event) {
    TimePoint end = std::chrono::steady_clock::now();
    TimePoint start = events[event].top();
    events[event].pop();
    Measurement diff = std::chrono::duration_cast<Measurement>(end - start);
    measurements[event].push_back(diff);
}

void Timer::print() {
    for (auto const& [event, times] : measurements) {
        std::cout << "Event: " << event << " (" << times.size() << ")" << std::endl;
        for (const Measurement& time : times) {
            double ms = ((double)time.count()) / 1000;
            std::cout << "\t- " << ms << "ms" << std::endl;
        }
    }
}
