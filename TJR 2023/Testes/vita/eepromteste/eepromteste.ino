#include "EEPROMLogger.h"


void setup()
{
Serial.begin(9600);
EEPROMLogger::print_log();
EEPROMLogger::print_debug();
EEPROMLogger::limpar();
}


void loop()
{
}