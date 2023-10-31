#ifndef _EEPROMLOGGER_H
#define _EEPROMLOGGER_H

#include <EEPROM.h>

namespace EEPROMLogger {

  // atual endereço a ser escrito/lido
  int EEPROM_i = 0;

  // codigos de cada condicao a ser salva no log
  enum EEPROM_CODE {
    NUL = 0xff,
    NL = 0xfe,
  
    OBJ = 0x01,
    ESQ,
    DIR,
    ENCR
  };

  // limpa a memoria eeprom, resetando cada valor para 0xFF
  void limpar(){
    for(unsigned int i=0; i < EEPROM.length(); i++)
      EEPROM.update(i, NUL);  
  }

  // retorna a memoria usada pelo eeprom
  int memused() {
    int n = 0;
    for(int i=0; i<EEPROM.length(); i++) {
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
      case ENCR: return "encruzilhada" ; break;
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
      case ENCR: return "EN"; break;
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
    for(int i=0; i<EEPROM.length();) {
      if(EEPROM.read(i) != NUL) {
        Serial.print("[");
  
        if(EEPROM.read(i) < 10) Serial.print("0");
        Serial.print(EEPROM.read(i++)); //min
  
        Serial.print(":");
  
        if(EEPROM.read(i) < 10) Serial.print("0");
        Serial.print(EEPROM.read(i++)); //sec
  
        Serial.print("] ");
        Serial.print(str_decod(EEPROM.read(i))); //c
        Serial.print(" ");

        if(EEPROM.read(i++) == OBJ) {
          Serial.print(EEPROM.read(i)); //val
        } else {
          Serial.print(EEPROM.read(i), BIN); //val
        }
        i++;
        
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
  }

  // printa o log de forma completa para debugs
  void print_debug() {
    for(int i=0; i<EEPROM.length();) {
      
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

  // adiciona uma nova linha para o log
  // parametros: 
  // mills: tempo, em milissegundos, desde q o codigo comecou a rodar
  // cod: codigo a ser adicionado, definido no enum EEPROM_CODE
  // val: valor a ser adicionado junto ao codigo
  void new_line(unsigned long mills, EEPROM_CODE cod, int val) {
    int secst = mills/1000;
    int mins = secst/60;
    int secs = secst - (60*mins);
  
    EEPROM.write(EEPROM_i++, mins);
    EEPROM.write(EEPROM_i++, secs);
    EEPROM.write(EEPROM_i++, cod);
    EEPROM.write(EEPROM_i++, val);
    EEPROM.write(EEPROM_i++, NL);
  }
}

#endif
