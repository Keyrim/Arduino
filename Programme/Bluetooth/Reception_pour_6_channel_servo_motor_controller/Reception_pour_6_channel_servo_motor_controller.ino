//pin 13 = txd
//pin 12 = rxd
#include <SoftwareSerial.h>
SoftwareSerial bluecom(13, 12);
 
char x [4];
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

  for(i=0; i<3; i++){
    while(!bluecom.available());
    mess = bluecom.read() ;
    x[i] = mess ; 
  }
  x[3] = 0;
  Mot = x ;
  Serial.println(Mot);

  }
  
}















