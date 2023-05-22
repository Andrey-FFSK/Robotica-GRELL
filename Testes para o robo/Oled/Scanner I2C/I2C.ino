/* I2C Address Finder
 *  for " Arduino LCD I2C Tutorial| How to Program LCD Display"
 *  subscribe for more arduino Tuorials and Projects

https://www.youtube.com/channel/UCM6rbuieQBBLFsxs...
 */

#include < wire.h>



void setup()

{
  Serial.begin (115200);
   while (!Serial)
    {
    }

  Serial.println ();
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;
  pinMode(13,OUTPUT); 
  digitalWrite(13,HIGH);
  Wire.begin();
  for (byte i = 1; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
      {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1); 
      } 
  } 
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
} 

void loop() {}
