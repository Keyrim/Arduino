//pin 13 = txd
//pin 12 = rxd
#include <SoftwareSerial.h>
SoftwareSerial BlueCom(13, 12); 


char mot [250];
char messageRecu ;
byte i = 0;
String Mot ;
int nombre ;

void reception(){
  
if(BlueCom.available()){
  while(messageRecu != '\n'){
      
    
if(BlueCom.available()){
      messageRecu  = BlueCom.read();
      mot[i] = messageRecu ;
      BlueCom.print(messageRecu);
      i++ ;
    }
    
  }
 i -- ;
 mot[i] = 0 ;

 i = 0;
 Mot = mot ; 
 BlueCom.println();
 BlueCom.println(Mot);
 nombre = Mot.toInt();
 //BlueCom.println(nombre);
 messageRecu = '}' ;
  
}
}

void setup() {
 BlueCom.begin(9600);
 Serial.begin(9600);
}

void loop() {

reception();

}











