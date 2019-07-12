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
    
    if(messageRecu.value == 0xF34CF734 || messageRecu.value == 0x7671E8B6)      //stick droit haut
    {
      digitalWrite(10,1);
 }
    if(messageRecu.value == 0x36D3E5EF || messageRecu.value == 0x45E4811D)      //stick droit bas
    {
      digitalWrite(9,1);
    }
     
     if(messageRecu.value == 0x51B3BBFF || messageRecu.value == 0x60C4572D)     //stick droit gauche
    {
      digitalWrite(8,1);
    }
     
     if(messageRecu.value == 0x784BBCEC || messageRecu.value == 0xFB70AE6E)     //stick droit droite
    {
      digitalWrite(11,1);
    }
     
     if(messageRecu.value == 0x8D25B54D)             //video
    {
      digitalWrite(8,0);
      digitalWrite(9,0);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }

    if(messageRecu.value == 0xFC056810)             //lumiere
    {
      delay(50);
      digitalWrite(8,1);
      digitalWrite(9,1);
      digitalWrite(10,1);
      digitalWrite(11,1);
      delay(50);
      digitalWrite(8,0);
      digitalWrite(9,0);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
     
      
      Recept.resume();
   }
   delay(1);
 }

