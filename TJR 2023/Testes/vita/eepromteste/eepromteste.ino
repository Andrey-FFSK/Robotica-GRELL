#include <EEPROM.h>

enum EEPROM_CODE {
  NUL = 0xff,
  NL = 0xfe,

  OBJ = 0x01,
  ESQ,
  DIR,
  ENCR,
};

unsigned int EEPROM_i = 0;

void clearEEPROM() {
  for(unsigned int i=0; i < EEPROM.length(); i++)
      EEPROM.update(i, NUL);
}

void print_raw() {
  for(unsigned int i=0; i<EEPROM.length(); i++) {
    if(EEPROM.read(i) != 255);
      Serial.print(EEPROM.read(i));
  }
}

String decod_c_ord(byte inp) {
  switch(inp) {
    case NL  : return "new line"    ; break;
    case NUL : return "vazio"       ; break;
    case OBJ : return "desviando"   ; break;
    case ESQ : return "90 esquerda" ; break;
    case DIR : return "90 direita"  ; break;
    case ENCR: return "encruzilhada"; break;
    default  : return "{{val}}"     ; break;
  }
}

String decod_c(byte inp) {
  switch(inp) {
    case NL  : return "\n"           ; break;
    case NUL : return ""             ; break;
    case OBJ : return "desviando "   ; break;
    case ESQ : return "90 esquerda " ; break;
    case DIR : return "90 direita "  ; break;
    case ENCR: return "encruzilhada "; break;
    default  : return String(inp)    ; break;
  }
}

String decod_c_full(byte inp) {
  switch(inp) {
    case NL  : return "NL"           ; break;
    case NUL : return ".."             ; break;
    case OBJ : return "dv"   ; break;
    case ESQ : return "eq" ; break;
    case DIR : return "dr"  ; break;
    case ENCR: return "en"; break;
    default  : return String(inp)    ; break;
  }
}

void print_ord() {
  for(int i=0; i<EEPROM.length(); i++) {
    byte b = EEPROM.read(i);
    if(b != NUL) {
      Serial.print(i);
      Serial.print(": ");
      Serial.print(b);
      Serial.print(" / ");
      Serial.println(decod_c_ord(b));
    }
  }
}

void print_decod() {
  for(int i=0; i<EEPROM.length();) {
    if(EEPROM.read(i) != NUL) {
      Serial.print("[");
      Serial.print(decod_c(EEPROM.read(i++)));
      Serial.print(":");
      Serial.print(decod_c(EEPROM.read(i++)));
      Serial.print("] ");
      Serial.print(decod_c(EEPROM.read(i++)));
      Serial.print(EEPROM.read(i++));
      Serial.print(decod_c(EEPROM.read(i++)));
    }else{
      i++;
    }
  }
}

void addLn(unsigned long mills, EEPROM_CODE code, int val) {
  int secst = mills/1000;
  int mins = secst/60;
  int secs = secst - (60*mins);

  EEPROM.put(EEPROM_i++, mins);
  EEPROM.put(EEPROM_i++, secs);
  EEPROM.write(EEPROM_i++, code);
  EEPROM.put(EEPROM_i++, val);
  EEPROM.write(EEPROM_i++, NL);
}

void print_full() {
  for(int i=0; i<EEPROM.length();) {
    
    int tmp_i = i;
    for(int j=0; j<8; j++) {
      Serial.print(EEPROM.read(i++), HEX);
      Serial.print(" ");
    }
    Serial.print(" / ");
    i = tmp_i;
    for(int j=0; j<8; j++) {
      Serial.print(decod_c_full(EEPROM.read(i++)));
      Serial.print(" ");
    }

    Serial.println("");
  }
}

void setup() {
  Serial.begin(9600);
  clearEEPROM();

  addLn(13500, OBJ, 5);
  addLn(28698, ESQ, 86);
  addLn(32213423, DIR, 100);
  
  Serial.println("dados codificados:");
  print_ord();
  Serial.println("--------------");

  Serial.println("dados decodificados:");
  print_decod();
  Serial.println("--------------");
  
  print_full();
  Serial.println("--------------");

}

void loop(){}