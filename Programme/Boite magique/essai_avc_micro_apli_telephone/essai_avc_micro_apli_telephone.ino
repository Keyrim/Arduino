//pin 13 = txd
//pin 12 = rxd
#include <SoftwareSerial.h>
SoftwareSerial BlueCom(13, 12);
 

long duration, distance;
char mot [255];
char messageRecu ;
byte i = 0;
String Mot ;
int nombre ;
int led;

void reception(){
  
  if(BlueCom.available()){
  
  messageRecu = BlueCom.read();
  mot[i] = messageRecu ;
  
  if(mot[i] == '*'){
    i = 255 ;
  }
  if(mot[i] == '#'){
    i ++ ;
    mot[i] = 0;
    Mot = mot;
    nombre = Mot.toInt();
    i = 255;
    Serial.println(Mot);
    Serial.println(nombre);
  }
  i++;
 }
}



void setup() {
 BlueCom.begin(9600);
 Serial.begin(9600);
 pinMode(9, OUTPUT);
 pinMode(8, OUTPUT);
}

void loop() {
  
 reception();
  
 
}











