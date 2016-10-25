листинг decryptor.bin

```asm
movc 0x40
in   R1
jfe  0x1a
in   R2
in   R3
sub  R2, R0
sub  R3, R0
lsl  R3
lsl  R3
lsl  R3
lsl  R3
or   R2, R3
xor  R2, R1
out  R2
jmp  0xe6
ret
```

аналог на C++

```C++
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
```