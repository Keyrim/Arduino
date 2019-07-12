#include <EEPROM.h>
char tab[500];
void setup() {
  Serial.begin(115200);
  for(int o = 0; o < 501; o++){
    Serial.print((char)EEPROM.read(o));
  }
  
}

void loop() {
  int i = 0;
  if(Serial.available()){
    EEPROM.write(i, Serial.read());
  }
  i++;
 
}
