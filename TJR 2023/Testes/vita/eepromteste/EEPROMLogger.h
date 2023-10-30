#include <EEPROM.h>

namespace EEPROMLogger {

  const int OBSTACULOS_ADDR = 0;
  int EEPROM_i = 0;
  
  enum EEPROM_CODE {
    NUL = 0xff,
    NL = 0xfe,
    EoF = 0xfd,
  
    OBJ = 0x01,
    ESQ,
    DIR,
    ENCR,
    LATA,
    MARROM
  };

  inline uint8_t get_obs() { return EEPROM.read(OBSTACULOS_ADDR); }
  inline void incr_obs() { EEPROM.write(OBSTACULOS_ADDR, get_obs() + 1); }

  void limpar(){
    for(unsigned int i=0; i < EEPROM.length(); i++)
      EEPROM.update(i, NUL);  
  }

 int memused() {
    int n = 0;
    for(int i=0; i<EEPROM.length(); i++) {
      if(EEPROM.read(i) != NUL)
        n++;
    }
    return n;
  } 

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
  
  String str_debugl(byte cod) {
    switch(cod) {
      case NL  : return "NL"; break;
      case NUL : return ".."; break;
      case OBJ : return "DV"; break;
      case ESQ : return "EQ"; break;
      case DIR : return "DR"; break;
      case ENCR: return "EN"; break;
      default: 
        String out = "";
        if(inp < 0x10)
          out += '0';
        out += String(inp, HEX);
        out.toUpperCase();
        return out;
        break;
    }
  }

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
        Serial.print(str_decod(EEPROM.read(i++))); //c
        Serial.print(" ");
        Serial.print(EEPROM.read(i++)); //val
        Serial.print(str_decod(EEPROM.read(i++))); //nl
      }else{
        i++;
      }
    }

    Serial.println("");

    Serial.print("obstaculos contados: ");
    Serial.println(get_obs());
    
    Serial.print("memoria usada: ");
    Serial.print(memused());
    Serial.print(" / ");
    Serial.println(EEPROM.length());
  }

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

  void new_line(unsigned long mills, EEPROM_CODE code, int val) {
    int secst = mills/1000;
    int mins = secst/60;
    int secs = secst - (60*mins);
  
    EEPROM.write(EEPROM_i++, mins);
    EEPROM.write(EEPROM_i++, secs);
    EEPROM.write(EEPROM_i++, code);
    EEPROM.write(EEPROM_i++, val);
    EEPROM.write(EEPROM_i++, NL);
  }
}
