_#include <IRremote.h>  //PIN 3 la led OK 
const int RECV_PIN = 2; 
IRrecv irrecv(RECV_PIN); 
decode_results messageRecu;
IRsend irLed;
void setup(){  
  Serial.begin(9600); 
  irrecv.enableIRIn();
  irrecv.blink13(true);
} void loop() {
   if (irrecv.decode(&messageRecu)) {     
    if (messageRecu.decode_type == NEC) {
      Serial.print("NEC: ");
    } else if (messageRecu.decode_type == SONY) {
      Serial.print("SONY: ");
    } else if (messageRecu.decode_type == RC5) {
      Serial.print("RC5: ");
    } else if (messageRecu.decode_type == RC6) {
      Serial.print("RC6: ");
    } else if (messageRecu.decode_type == UNKNOWN) {
      Serial.print("UNKNOWN: ");
    }
    Serial.println(messageRecu.value, HEX);


    if(messageRecu.value == 0x8D25B54D)     //video
    {
      Serial.println("on/off");
    irLed.sendRC5(0x84c ,32);
    
}
    
          
   
    
    
     
     
     
     
     
     
     irrecv.enableIRIn(); 
     
   irrecv.resume();
   }
}
   


