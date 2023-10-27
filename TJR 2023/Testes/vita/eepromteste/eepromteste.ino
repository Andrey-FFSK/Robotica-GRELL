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

int EEPROM_memused() {
  int n = 0;
  for(int i=0; i<EEPROM.length(); i++) {
    if(EEPROM.read(i) != NUL)
      n++;
  }
  return n;
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
    case OBJ : return "desviando    "; break;
    case ESQ : return "90 esquerda  "; break;
    case DIR : return "90 direita   "; break;
    case ENCR: return "encruzilhada "; break;
    default  : return "codigo n reconhecido"; break;
  }
}

String decod_c_full(byte inp) {
  switch(inp) {
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

void print_ord() {
  for(int i=0; i<EEPROM.length(); i++) {
    byte b = EEPROM.read(i);
    if(b != NUL) {
      Serial.print(i);
      Serial.print(": ");
      char buf[5];
      sprintf(buf, "%02X", b);
      Serial.print(buf);
      Serial.print(" / ");
      Serial.println(decod_c_ord(b));
    }
  }
}

void print_decod() {
  for(int i=0; i<EEPROM.length();) {
    if(EEPROM.read(i) != NUL) {
      Serial.print("[");

      if(EEPROM.read(i) < 10) Serial.print("0");
      Serial.print(EEPROM.read(i++)); //min

      Serial.print(":");

      if(EEPROM.read(i) < 10) Serial.print("0");
      Serial.print(EEPROM.read(i++)); //sec

      Serial.print("] ");
      Serial.print(decod_c(EEPROM.read(i++))); //c
      Serial.print(EEPROM.read(i++)); //val
      Serial.print(decod_c(EEPROM.read(i++))); //nl
    }else{
      i++;
    }
  }
}

void print_full() {
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
      Serial.print(decod_c_full(EEPROM.read(i++)));
      Serial.print(" ");
    }

    Serial.println("");
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

void setup() {
  Serial.begin(9600);
  clearEEPROM();

  addLn(30000, OBJ, 5);
  addLn(60000, ESQ, 86);
  addLn(90000, DIR, 100);
  addLn(120000, ENCR, 69);

  Serial.println("dados decodificados:");
  print_decod();
  Serial.println("--------------");
  
  Serial.print("memoria usada: ");
  Serial.print(EEPROM_memused());
  Serial.print(" / ");
  Serial.println(EEPROM.length());
  print_full();
  Serial.println("--------------");
}

void loop(){}
