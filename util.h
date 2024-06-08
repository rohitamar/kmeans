#include <iostream>
#include <array>

template<typename T, size_t N>
std::istream& operator>>(std::istream& is, std::array<T, N>& arr) {
    for(size_t i = 0; i < N; i++) {
        is >> arr[i];
    }
    return is;
}

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& os, std::array<T, N>& arr) {
    for(size_t i = 0; i < N; i++) {
        os << arr[i] << " ";
    }
    return os;
}