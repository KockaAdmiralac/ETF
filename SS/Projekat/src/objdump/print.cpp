#include <iostream>
#include "objdump/print.hpp"

void printN(std::string str, size_t times) {
    for (size_t i = 0; i < times; ++i) {
        std::cout << str;
    }
}

void printRow(std::vector<std::string>& row, std::vector<size_t>& sizes) {
    std::cout << "║";
    for (size_t i = 0; i < row.size(); ++i) {
        std::cout << " " << row[i];
        printN(" ", sizes[i] - row[i].size() + 1);
        if (i != row.size() - 1) {
            std::cout << "│";
        }
    }
    std::cout << "║" << std::endl;
}

void printRowWithBreakpoints(std::vector<size_t>& maxColumnSizes, std::string startChar, std::string endChar, std::string regularChar, std::string breakpointChar) {
    std::cout << startChar;
    for (size_t i = 0; i < maxColumnSizes.size(); ++i) {
        printN(regularChar, maxColumnSizes[i] + 2);
        if (i != maxColumnSizes.size() - 1) {
            std::cout << breakpointChar;
        }
    }
    std::cout << endChar << std::endl;
}

void printTable(std::vector<std::string> columns, std::vector<std::vector<std::string>> rows) {
    std::vector<size_t> maxColumnSizes(columns.size(), 0);
    for (size_t i = 0; i < columns.size(); ++i) {
        if (maxColumnSizes[i] < columns[i].length()) {
                maxColumnSizes[i] = columns[i].length();
        }
    }
    for (std::vector<std::string>& row : rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (maxColumnSizes[i] < row[i].length()) {
                maxColumnSizes[i] = row[i].length();
            }
        }
    }
    printRowWithBreakpoints(maxColumnSizes, "╔", "╗", "═", "╤");
    printRow(columns, maxColumnSizes);
    printRowWithBreakpoints(maxColumnSizes, "║", "║", "─", "┼");
    for (std::vector<std::string>& row : rows) {
        printRow(row, maxColumnSizes);
    }
    printRowWithBreakpoints(maxColumnSizes, "╚", "╝", "═", "╧");
}
