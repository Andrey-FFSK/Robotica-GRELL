#ifndef _EEPROMLOGGER_H
#define _EEPROMLOGGER_H

#include <EEPROM.h>

namespace EEPROMLogger {

    // endereço segurando o endereço a ser escrito/lido (lendo isso dnv ta meio confuso)
    const uint8_t EEPROM_I_ADDR = 0x00;

    // codigos de cada condicao a ser salva no log
    enum EEPROM_CODE {
        NUL = 0x00,
        NL,
    
        OBJ,
        ESQ,
        DIR,
        MAR,
        LAT
    };

    // limpa a memoria eeprom, resetando cada valor para 0x00
    void limpar(){
        for(unsigned int i = 0; i < EEPROM.length(); i++)
        EEPROM.update(i, NUL);  
    }
    

    // retorna a memoria usada pelo eeprom
    int memused() {
        unsigned int n = 0;
        for(unsigned int i=0; i<EEPROM.length(); i++) {
        if(EEPROM.read(i) != NUL)
            n++;
        }
        return n;
    } 

    // string retornando a versao decodificada de cada condicao definida no EEPROM_CODE
    String str_decod(byte cod) {
        switch(cod) {
        case NL  : return "\n"           ; break;
        case NUL : return ""             ; break;
        case OBJ : return "desviando"    ; break;
        case ESQ : return "90 esquerda"  ; break;
        case DIR : return "90 direita"   ; break;
        case MAR: return "marrom" ; break;
        case LAT: return "latinha" ; break;
        default  : return "codigo n reconhecido"; break;
        }
    }

    // mesma coisa do str_decod, mas de forma mais curta pro debug ficar mais bonito :)
    String str_debug(byte cod) {
        switch(cod) {
        case NL  : return "NL"; break;
        case NUL : return ".."; break;
        case OBJ : return "DV"; break;
        case ESQ : return "EQ"; break;
        case DIR : return "DR"; break;
        case MAR: return "MR" ; break;
        case LAT: return "LT" ; break;        
        default: 
            String out = "";
            if(cod < 0x10)
            out += '0';
            out += String(cod, HEX);
            out.toUpperCase();
            return out;
            break;
        }
    }

    // printa o log👍
    void print_log() {
        for(unsigned int i = sizeof(uint16_t); i<EEPROM.length();) {
            if(EEPROM.read(i) != NUL) { //[ i0:i1 ] i2 i3?<-4? i5?(3)
                Serial.print("[");
        
                if(EEPROM.read(i) < 10) Serial.print("0");
                Serial.print(EEPROM.read(i++)); //min
        
                Serial.print(":");
        
                if(EEPROM.read(i) < 10) Serial.print("0");
                Serial.print(EEPROM.read(i++)); //sec
        
                Serial.print("] ");
                Serial.print(str_decod(EEPROM.read(i++))); //c
                Serial.print(" ");

                if(EEPROM.read(i) != NL) {
                    byte val = EEPROM.read(i++);
                    byte frmt = EEPROM.read(i++);
                    if(frmt == BIN && val < 0b100)
                        Serial.print("0");
                    Serial.print(val, frmt);
                }

                Serial.print(str_decod(EEPROM.read(i++))); //nl
            }else{
                i++;
            }
        }

        Serial.println("");
        
        Serial.print("memoria usada: ");
        Serial.print(memused());
        Serial.print(" / ");
        Serial.println(EEPROM.length());
        Serial.println("//----------------*----------------//");
    }

    // printa o log de forma completa para debugs
    void print_debug() {
        for(unsigned int i=0; i<EEPROM.length();) {
        
        int tmp_i = i;
        for(int j=0; j<8; j++) {
            char buf[5];
            sprintf(buf, "%02X", EEPROM.read(i++));
            Serial.print(buf);
            Serial.print(" ");
        }
        Serial.print(" / ");
        i = tmp_i;
        for(int j=0; j<8; j++) {
            Serial.print(str_debug(EEPROM.read(i++)));
            Serial.print(" ");
        }
    
        Serial.println("");
        }
    }

    /*
    adiciona uma nova linha para o log
    parametros: 
     - mills          : tempo, em milissegundos, desde q o codigo comecou a rodar
     - cod            : codigo a ser adicionado, definido no enum `EEPROM_CODE`
     - val  (opcional): valor a ser adicionado junto ao codigo
     - fmrt (opcional): formato no qual o valor será adicionado (DEC, BIN, HEX)
    */
    void new_line(unsigned long mills, EEPROM_CODE cod, int val = 0xffff, int frmt = DEC) {
        uint16_t EEPROM_i = EEPROM.read(EEPROM_I_ADDR);
        int secst = mills/1000;
        int mins = secst/60;
        int secs = secst - (60*mins);
    
        EEPROM.write(EEPROM_i++, mins);
        EEPROM.write(EEPROM_i++, secs);
        EEPROM.write(EEPROM_i++, cod);
        if(val != 0xffff) {
            EEPROM.write(EEPROM_i++, val);
            EEPROM.write(EEPROM_i++, frmt);
        }
        
        EEPROM.write(EEPROM_i++, NL);

        EEPROM.put(EEPROM_I_ADDR, EEPROM_i);
    }
}

#endif
