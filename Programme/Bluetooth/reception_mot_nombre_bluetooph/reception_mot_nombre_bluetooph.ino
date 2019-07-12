#include <SoftwareSerial.h>
SoftwareSerial BlueCom(13, 12);  //pin 12 = rxd pin 13 = txd


char mot [250];
char messageRecu ;
byte i = 0;
String Mot ;
int nombre ;

void reception(){
  while(messageRecu != '\r'){
      
if(BlueCom.available()){  
      messageRecu  = BlueCom.read();
      BlueCom.print(messageRecu);
      mot[i] = messageRecu ;
      i++ ;
    }    
  }
 i -- ;
 mot[i] = 0 ;
 i = 0;
 Mot = mot ; 
 nombre = Mot.toInt();
 messageRecu = '}' ;  
}

void setup() {
 BlueCom.begin(9600);
 Serial.begin(9600);
}

void loop() {
reception();
                                              //fin pour eteindre une lumiere 
}











