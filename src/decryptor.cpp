/**
 * decryptor.bin reversed
 * @file decryptor.cpp
 *
 * build command
 *    g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror decryptor.cpp -o decryptor
 * run command
 *    ./decryptor input.txt
 */
#include <iostream>
#include <fstream>

int main(int, char** argv) {
    std::ifstream in;
    in.open(argv[1]);
    uint8_t r0, r1, r2, r3;
    r0 = 0x40;
    while(in >> r1) {
        in >> r2 >> r3;
        r2 -= r0;
        r3 -= r0;
        r3 <<= 4;
        r2 |= r3;
        r2 ^= r1;
        std::cout << r2;
    }
    return 0;
}