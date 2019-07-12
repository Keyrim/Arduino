//pin 13 = txd
//pin 12 = rxd
#include <SoftwareSerial.h>
SoftwareSerial bluecom(13, 12);
 
char x [3];
char y [3];
char reception [8];
char mess ;
byte i = 0;
String Mot ;
int nombre ;

void setup() {
 bluecom.begin(9600);
 Serial.begin(9600);
}

void loop() {

if(bluecom.available()){
  
  for(int n=0; n<8; n++){
    
    while(!bluecom.available());
    mess = bluecom.read();
    reception [n] = mess ;
    
    }
    Mot = reception ;
    Serial.print(Mot) ;
    Serial.print("  ");
    
  }
  
}















