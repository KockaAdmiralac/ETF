#include <sstream>
#include "keyboard.hpp"

Keyboard::KeyboardPosition::KeyboardPosition(int comb, char key) : key(key) {
    row = comb / QWERTY_KEYBOARD_WIDTH;
    col = comb % QWERTY_KEYBOARD_WIDTH;
}

Keyboard::KeyboardPosition::operator int() {
    return row * QWERTY_KEYBOARD_WIDTH + col;
}

const char Keyboard::QWERTY_KEYBOARD_MAPPING[QWERTY_KEYBOARD_HEIGHT][QWERTY_KEYBOARD_WIDTH] = {
    {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
    {'\0', 'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',  'o',  'p',  '\0'},
    {'\0', 'a',  's',  'd',  'f',  'g',  'h',  'j',  'k',  'l',  '\0', '\0'},
    {'\0', '\0', 'z',  'x',  'c',  'v',  'b',  'n',  'm',  '\0', '\0', '\0'},
    {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'}
};

Keyboard::Keyboard() {
    for (int i = 0; i < QWERTY_KEYBOARD_HEIGHT; ++i) {
        for (int j = 0; j < QWERTY_KEYBOARD_WIDTH; ++j) {
            KeyboardPosition pos(i, j, QWERTY_KEYBOARD_MAPPING[i][j]);
            if (pos.key != '\0') {
                positionToChar.insert({pos, pos.key});
                charToPosition.insert({pos.key, pos});
            }
        }
    }
}

std::string Keyboard::getNeighbors(char c) {
    std::stringstream stream;
    KeyboardPosition pos(charToPosition[c], c);
    if (QWERTY_KEYBOARD_MAPPING[pos.row-1][pos.col] != '\0') {
        stream << QWERTY_KEYBOARD_MAPPING[pos.row-1][pos.col];
    }
    if (QWERTY_KEYBOARD_MAPPING[pos.row+1][pos.col] != '\0') {
        stream << QWERTY_KEYBOARD_MAPPING[pos.row+1][pos.col];
    }
    if (QWERTY_KEYBOARD_MAPPING[pos.row][pos.col-1] != '\0') {
        stream << QWERTY_KEYBOARD_MAPPING[pos.row][pos.col-1];
    }
    if (QWERTY_KEYBOARD_MAPPING[pos.row][pos.col+1] != '\0') {
        stream << QWERTY_KEYBOARD_MAPPING[pos.row][pos.col+1];
    }
    return stream.str();
}
