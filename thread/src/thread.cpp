#include <iostream>
#include <charconv>
#include<array>

using namespace std;

int main() {
    array<char, 10> str;
    to_chars(str.data(), str.data() + str.size(), msgIdx++);
    // std::to_chars(str.data(), str.data() + str.size(), 42);
    cout << str.data();
    return 0;
}