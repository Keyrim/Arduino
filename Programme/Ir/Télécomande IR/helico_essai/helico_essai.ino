#include <IRremote.h>

const char DIN_RECEPTEUR_INFRAROUGE = 2;

IRrecv Recept (DIN_RECEPTEUR_INFRAROUGE);

decode_results messageRecu;



void setup()
 {
  Serial.begin(9600);
  Recept.enableIRIn();
  Recept.blink13(true);
  pinMode(8 , OUTPUT);
  pinMode(9 , OUTPUT);
  pinMode(10 , OUTPUT);
  pinMode(11 , OUTPUT);
 }

void loop()
 {
   if (Recept.decode(&messageRecu)) {

    if(messageRecu.value == 0x69D14705){
      digitalWrite(8,1);
      digitalWrite(9,1);
      digitalWrite(10,1);
      digitalWrite(11,1);
    }
    if(messageRecu.value == 0x7F40FFCB || messageRecu.value == 0x884E16EE){
      digitalWrite(8,1);
      digitalWrite(9,1);
      digitalWrite(10,1);
      digitalWrite(11,0);
    }
    if(messageRecu.value == 0x78EF2729 || messageRecu.value == 0xB092A1C4){
      digitalWrite(8,1);
      digitalWrite(9,1);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
    if(messageRecu.value == 0xBC882654 || messageRecu.value == 0x2FBBC5D4){
      digitalWrite(8,1);
      digitalWrite(9,0);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
    if(messageRecu.value == 0x875A8988){
      digitalWrite(8,0);
      digitalWrite(9,0);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
     Recept.resume();
   }
  
 }
     
     
