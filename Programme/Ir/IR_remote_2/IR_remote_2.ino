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
    
    if(messageRecu.value == 0x69D14705 ||messageRecu.value == 0xFBBE00F6  ||messageRecu.value == 0xAC32676A  ||messageRecu.value == 0x18C1133B  ||messageRecu.value == 0x91521A8D  ||messageRecu.value == 0x67EF97B1  ||messageRecu.value == 0x87615584  ||messageRecu.value == 0x3AE4867C) 
    // haut vers bas 1
    {
      digitalWrite(8,1);
      digitalWrite(9,1);
      digitalWrite(10,1);
      digitalWrite(11,1);
    }
    if(messageRecu.value == 0xBB698000 ||messageRecu.value == 0xF2B324D5 ||messageRecu.value == 0x5B07EC0A ||messageRecu.value == 0xCDB4A4DA ||messageRecu.value == 0xF621499 ||messageRecu.value == 0x96D43C4E ||messageRecu.value == 0xA9B66015 ||messageRecu.value == 0x43B54716 )   
    // haut vers bas 2
    {
      digitalWrite(8,1);
      digitalWrite(9,1);
      digitalWrite(10,1);
      digitalWrite(11,0);
    }
    if(messageRecu.value == 0xCBD5BBF1 ||messageRecu.value == 0x3A241D7A ||messageRecu.value == 0xD31796A4 ||messageRecu.value == 0x875A66E9 ||messageRecu.value == 0x38A70C9B ||messageRecu.value == 0x61ED60F ||messageRecu.value == 0xAED3EE31 ||messageRecu.value == 0x3929BDF8 )   
    // haut vers bas 3
    {
      digitalWrite(8,1);
      digitalWrite(9,1);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
    if(messageRecu.value == 0xA8F919F9 ||messageRecu.value == 0x21AB426F ||messageRecu.value == 0x4414C17B ||messageRecu.value == 0xCD06DAA  ||messageRecu.value == 0x4E956F10 ||messageRecu.value == 0xC28A301C ||messageRecu.value == 0xE475FDB   ||messageRecu.value == 0xA08D0814 )   
    // haut vers bas 4
    {
      digitalWrite(8,1);
      digitalWrite(9,0);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
    if(messageRecu.value == 0x7C853DDF ||messageRecu.value == 0x4E956F10 ||messageRecu.value == 0xBCBD80AF ||messageRecu.value == 0x99B437B2 ||messageRecu.value == 0xCCE89239 ||messageRecu.value == 0xA3BBFAC4 ||messageRecu.value == 0x3868133E  ||messageRecu.value == 0x875A8988 )   
    // haut vers bas 5
    {
      digitalWrite(8,0);
      digitalWrite(9,0);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
   
     
     if(messageRecu.value == 0x15D67EAB)             //photo
    {
      digitalWrite(8,0);
      digitalWrite(9,0);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }

    if(messageRecu.value == 0xFC056810)              //lumiere
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

