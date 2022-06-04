#ifndef _FILE_UTILS_HPP
#define _FILE_UTILS_HPP
#include <iostream>
#include <vector>

template<typename T>
inline void relocWrite(std::ostream& stream, T data) {
    stream.write((char*) &data, sizeof(T));
}

inline void writeString(std::ostream& stream, std::string& str) {
    relocWrite(stream, str.size());
    stream.write(str.c_str(), str.size());
}

template<typename T>
inline void writeVector(std::ostream& stream, std::vector<T>& vect) {
    relocWrite(stream, vect.size());
    for (T& data : vect) {
        relocWrite(stream, data);
    }
}

template<typename T>
inline T relocRead(std::istream& stream) {
    T data;
    stream.read((char*) &data, sizeof(T));
    return data;
}

inline std::string readString(std::istream& stream) {
    std::string str;
    std::size_t size = relocRead<std::size_t>(stream);
    str.resize(size);
    stream.read(&str[0], size);
    return str;
}

template<typename T>
inline void readVector(std::istream& stream, std::vector<T>& vect) {
    std::size_t size = relocRead<std::size_t>(stream);
    for (std::size_t i = 0; i < size; ++i) {
        vect.push_back(relocRead<T>(stream));
    }
}
#endif
