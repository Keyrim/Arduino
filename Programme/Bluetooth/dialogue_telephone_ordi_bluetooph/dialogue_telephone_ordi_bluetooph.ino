//pin 13 = txd
//pin 12 = rxd
#include <SoftwareSerial.h>
SoftwareSerial BlueCom(13, 12); 


char motTel [250];
char motOrdi [250];
char messageRecuOrdi ;
char messageRecuTel ;
byte i = 0;
byte a = 0;
String MotTel ;
String MotOrdi ;
int nombreRecuOrdi ;

void convertOrdi (){
  
  if(Serial.available()){
    
    nombreRecuOrdi = (int)messageRecuOrdi - 48 ;
    nombreRecuOrdi = nombreRecuOrdi  * 10 ;
  }
  
}

void setup() {
 BlueCom.begin(9600);
 Serial.begin(9600); 
 BlueCom.println();
 Serial.println();
}

void loop() {

if(BlueCom.available()){
  messageRecuTel  = BlueCom.read();
  
  if(messageRecuTel == '#'){
    motTel[i] = 0 ;
    i = 0;
    MotTel = motTel ;
    Serial.print("Telephone:  ");
    Serial.println(motTel);
    BlueCom.print("Telephone:  ");
    BlueCom.println(motTel);
       
    }
     
    else{
      motTel[i] = messageRecuTel ;
    i++ ;
    }
}


    if(Serial.available()){
  messageRecuOrdi  = Serial.read();
    
  
  if(messageRecuOrdi == '\r'){
    motOrdi[a] = 0 ;
    a = 0;
    MotOrdi = motOrdi ;
       Serial.print("Ordinateur:  ");
       Serial.println(motOrdi);
       BlueCom.print("Ordinateur:  ");
       BlueCom.println(motOrdi);
       
    }
     
    else{
      motOrdi[a] = messageRecuOrdi ;
    a++ ;
    }
  }
}













