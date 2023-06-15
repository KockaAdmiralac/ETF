#pragma once
#include <chrono>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using TimePoint = std::chrono::steady_clock::time_point;
using Measurement = std::chrono::microseconds;

class Timer {
public:
    static void start(const std::string& event);
    static void end(const std::string& event);
    static void print();
private:
    static std::unordered_map<std::string, std::stack<TimePoint>> events;
    static std::unordered_map<std::string, std::vector<Measurement>> measurements;
};
