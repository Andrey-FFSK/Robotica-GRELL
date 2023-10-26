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

    NL = 0xff
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

    int secst = mills / 1000;
    int mins = secst / 60;
    int secs = secst - (60*mins);

    string mins_str = std::to_string(mins);
    string secs_str = std::to_string(secs);

    EEPROM[EEPROM_i++] = mins_str.at(mins_str.length() - 1);
    EEPROM[EEPROM_i++] = secs_str.at(0);
    EEPROM[EEPROM_i++] = secs_str.at(1);

    // EEPROM[EEPROM_i++] = TIME_INI;
    // EEPROM[EEPROM_i++] = mins_str.at(mins_str.length() - 2);
    // EEPROM[EEPROM_i++] = mins_str.at(mins_str.length() - 1);
    // EEPROM[EEPROM_i++] = TIME_SEP;
    // EEPROM[EEPROM_i++] = secs_str.at(0);
    // EEPROM[EEPROM_i++] = secs_str.at(1);
    // EEPROM[EEPROM_i++] = TIME_END;

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
        // case TIME_INI: return "tempo "        ; break;
        // case TIME_SEP: return ": "        ; break;
        // case TIME_END: return "] "        ; break;
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
        // case TIME_INI: return "[ "        ; break;
        // case TIME_SEP: return ":"         ; break;
        // case TIME_END: return " ] "       ; break;
        default: 
            string out = "";
            out += inp;
            return out;
            break;
    }
}

void print_decode() {
    for(int i=0; i<EEPROM_S;) {
        if(EEPROM[i] == NUL) {
            i++;
            continue;
        }

        cout << "[";
        cout << decod_c(EEPROM[i++]);
        cout << ":";
        cout << decod_c(EEPROM[i++]);
        cout << decod_c(EEPROM[i++]);
        cout << "] ";
        while(EEPROM[i] != NL)
            cout << decod_c(EEPROM[i++]);
        cout << decod_c(EEPROM[i++]);
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
