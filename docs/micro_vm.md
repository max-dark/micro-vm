Характеристики машины

 - 16 регистров общего назначения R0-R15(8 бит каждый)
 - 8мибитную адресацию программы(счетчик команд 8 бит)
 - 256 байт памяти под програмный код
 - 1 "флаговый"(flag) регистр - только IN

На вход подается бинарный файл с программой и входной текстовый файл данных


есть 2 типа команд:
- 1й тип(2 параметра) состоит из 8 бит кода команды и 2х операндов:
    -    биты 0-3 - 1й параметр(регистр)
    -    биты 4-7 - 2й параметр(регистр)  
    некоторые комманды(LSL, INC) не имеют второго регистра. в этом случае биты 4-7 игнорируются
- 2й тип(1 параметр) состоит из 8 бит кода команды и 8 бит константы(MOVC) либо смещение перехода(JZ, JNZ, JFE)

таблица команд
```
мнемоника     опкод комментарий
INC  Rx        0x01 инкремент регистра x
DEC  Rx        0x02 декремент регистра x
MOV  Rx, Ry    0x03 копирует регистр Ry в Ry
MOVC "const"   0x04 записывает константу в R0. 2й тип команды
LSL  Rx        0x05 сдвиг регистра Rx на 1 бит влево
LSR  Rx        0x06 сдвиг регистра Rx на 1 бит вправо
JMP  addr      0x07 безусловный переход по смещению "addr". все команды перехода имеют 2й тип
JZ   addr      0x08 условный переход по смещению "addr"(если флаг == 0). В этой работе не используется
JNZ  addr      0x09 условный переход по смещению "addr"(если флаг != 0). В этой работе не используется
JFE            0x0A условный переход, если достигнут конец файла(см. IN)
RET            0x0B окончание работы(останов) VM
ADD  Rx, Ry    0x0C Rx = Rx + Ry
SUB  Rx, Ry    0x0D Rx = Rx - Ry
XOR  Rx, Ry    0x0E Rx = Rx xor Ry
OR   Rx, Ry    0x0F Rx = Rx bit_or Ry
IN   Rx        0x10 чтение байта из файла в Rx и установка флага "конец файла", если он был достигнут
OUT  Rx        0x11 запись байта из Rx в файл/вывод на экран
```