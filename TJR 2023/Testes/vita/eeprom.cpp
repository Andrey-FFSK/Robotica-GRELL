#include <iostream>
#include <string>

#define EEPROM_S 1024

using namespace std;

enum EEPROM_C {
    NUL = 0x0,
    OBJ,
    ESQ,
    DIR,
    ENCRU,

    TIME_INI = 0xfb,
    TIME_END = 0xfc,
    L_INI = 0xfd,
    NL = 0xfe,
    L_EOF = 0xff
};

unsigned char EEPROM[EEPROM_S];
int EEPROM_i = 0;

void clear() {
    for(int i=0; i<EEPROM_S; i++)
        EEPROM[i] = '0';
}

void addLn(int time, EEPROM_C code, int val, )

void writeStr(string str) {
    for(int i = 0; i< str.length(); i++) {
        EEPROM[EEPROM_i++] = str.at(i);
    }
    EEPROM[EEPROM_i++] = '\n';
}

int main() {

    //setup
    clear();
    
    for(int i=0; i<EEPROM_S; i++) {
        printf("%c", EEPROM[i]);
    }


    //loop


    return 0;
}