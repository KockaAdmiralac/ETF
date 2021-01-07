#ifndef _keyboard_hpp
#define _keyboard_hpp
#include <string>
#include <unordered_map>

class Keyboard {
    struct KeyboardPosition {
        int row, col;
        char key;
        KeyboardPosition(int row, int col, char key) :
            row(row), col(col), key(key) {}
        KeyboardPosition(int comb, char key);
        operator int();
    };
    public:
        Keyboard();
        std::string getNeighbors(char c);
    private:
        std::unordered_map<int, char> positionToChar;
        std::unordered_map<char, int> charToPosition;
        static const int QWERTY_KEYBOARD_HEIGHT = 5;
        static const int QWERTY_KEYBOARD_WIDTH = 12;
        static const char QWERTY_KEYBOARD_MAPPING[QWERTY_KEYBOARD_HEIGHT][QWERTY_KEYBOARD_WIDTH];
};

#endif
