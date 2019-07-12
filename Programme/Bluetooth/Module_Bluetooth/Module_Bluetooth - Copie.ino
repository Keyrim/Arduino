

#include <SoftwareSerial.h>

SoftwareSerial BlueCom(10, 11);
 
int MessageRecu;

void setup() {

 BlueCom.begin(9600);
 Serial.begin(9600);
 

}

void loop() {

   if (BlueCom.available())
   {

     MessageRecu = BlueCom.read();
     Serial.write(MessageRecu);
     
   }

}


