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

    TIME_INI = 0xfa,
    TIME_SEP,
    TIME_END,
    L_INI,

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

    float secs = mills/1000.0f;
    int mins = (int)secs % 60;
    float sec_ = secs - (mins * 60.0f);

    string mins_str = std::to_string(mins);
    string secs_str = std::to_string(sec_);

    EEPROM[EEPROM_i++] = TIME_INI;
    EEPROM[EEPROM_i++] = mins_str.at(mins_str.length() - 2);
    EEPROM[EEPROM_i++] = mins_str.at(mins_str.length() - 1);
    EEPROM[EEPROM_i++] = TIME_SEP;
    EEPROM[EEPROM_i++] = secs_str.at(secs_str.length() - 2);
    EEPROM[EEPROM_i++] = secs_str.at(secs_str.length() - 1);
    EEPROM[EEPROM_i++] = TIME_END;
    EEPROM[EEPROM_i++] = code;

    string val_str = std::to_string(val);
    char n3 = val_str.at(val_str.length() - 1);
    char n2 = (val_str.length() == 1) ? '0' : val_str.at(val_str.length() - 2);
    char n1 = (val_str.length() <= 2) ? '0' : val_str.at(val_str.length() - 3);
    
    EEPROM[EEPROM_i++] = n1;
    EEPROM[EEPROM_i++] = n2;
    EEPROM[EEPROM_i++] = n3;

    EEPROM[EEPROM_i++] = NL;
}

string decod_c_debug(unsigned char inp) {
    switch(inp) {
        case NL   : return "new line "    ; break;
        case NUL  : return "porra nenhum "; break;
        case OBJ  : return "desviando "   ; break;
        case ESQ  : return "90 esquerda " ; break;
        case DIR  : return "90 direita "  ; break;
        case ENCRU: return "encruzilhada "; break;
        case TIME_INI: return "[ "        ; break;
        case TIME_SEP: return ": "        ; break;
        case TIME_END: return "] "        ; break;
        default: return "{{val}} " ; break;
    }
}

string decod_c(unsigned char inp) {
    switch(inp) {
        case NL   : return "\n"    ; break;
        case NUL  : return ""; break;
        case OBJ  : return "desviando "   ; break;
        case ESQ  : return "90 esquerda " ; break;
        case DIR  : return "90 direita "  ; break;
        case ENCRU: return "encruzilhada "; break;
        case TIME_INI: return "[ "        ; break;
        case TIME_SEP: return ":"         ; break;
        case TIME_END: return " ] "       ; break;
        default: 
            string out = "";
            out += inp;
            return out;
            break;
    }
}

void print_decode() {
    for(int i=0; i<EEPROM_S; i++) {
        if(EEPROM[i] == NUL)
            continue;
        
        cout << decod_c(EEPROM[i]);
    }
}

void print_raw() {
    for(int i=0; i<EEPROM_S; i++) {
        if(EEPROM[i] == NUL)
            continue;
        
        cout << i << ": ";
        cout << EEPROM[i] << " / " << decod_c_debug(EEPROM[i]).c_str() << endl;
    }
}

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

    cout << "-----------" << endl;
    print_raw();
    cout << endl << "-----------" << endl;

    cout << "memoria usada: " << EEPROM_free() << " / " << EEPROM_S << endl;


    //loop


    return 0;
}