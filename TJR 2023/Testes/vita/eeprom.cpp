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
        EEPROM[i] = NUL;
}

int EEPROM_free() {
    int n = 0;
    for(int i=0; i<EEPROM_S; i++) {
        if(EEPROM[i] != NUL)
            n++;
    }
    return n;
}

void print() {
    for(int i=0; i<EEPROM_S; i++) {
        if(EEPROM[i] != NUL)
            printf("%c", EEPROM[i]);
    }
}

void addLn(unsigned long mills, EEPROM_C code, int val) {
    int secs = mills / 1000;
    int mins = secs / 60;

    EEPROM[EEPROM_i++] = TIME_INI;
    EEPROM[EEPROM_i++] = mins;
    EEPROM[EEPROM_i++] = ':';
    EEPROM[EEPROM_i++] = secs;
    EEPROM[EEPROM_i++] = TIME_END;

    EEPROM[EEPROM_i++] = code;
    EEPROM[EEPROM_i++] = val;

    EEPROM[EEPROM_i++] = NL;
}

void print_decode() {
    for(int i=0; i<EEPROM_S; i++) {
        switch(EEPROM[i]) {
            case NUL: break;
            case OBJ: printf("desviando "); break;
            case ESQ: printf("90 esquerda "); break;
            case DIR: printf("90 direita "); break;
            case ENCRU: printf("encruzilhada "); break;
            case TIME_INI: printf("[ "); break;
            case TIME_END: printf("] "); break;
            case NL: printf("\n"); break;
            default: printf("%u", (int)EEPROM[i]); break;
        }
    }
}

/*void addLn(int time, EEPROM_C code, int val) {
    int hour = time % 60;
    int secs = time - 60*hour;

    string code_str = "";
    switch(code) {
        case OBJ: code_str = "desviando"; break;
        case ESQ: code_str = "90 esquerda"; break;
        case DIR: code_str = "90 direita"; break;
        case ENCRU: code_str = "encruzilhada"; break;
    }
}*/

void writeStr(string str) {
    for(int i = 0; i< str.length(); i++) {
        EEPROM[EEPROM_i++] = str.at(i);
    }
    EEPROM[EEPROM_i++] = '\n';
}

int main() {

    //setup
    clear();
    addLn((unsigned long)13500, OBJ, 5);
    addLn((unsigned long)28800, ESQ, 86);
    addLn((unsigned long)153800, DIR, 100);

    cout << "dados n codificados:" << endl;
    print();
    cout << endl << "-------------" << endl;
    cout << "decodificados:" << endl;
    print_decode();
    cout << endl << "-----------" << endl;
    cout << "memoria usada: " << EEPROM_free << " / " << EEPROM_S << endl;


    //loop


    return 0;
}