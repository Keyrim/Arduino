 
 int joysticx;
 int x;
 int joysticy;
 int y;
 
 
 
#include <IRremote.h>  //PIN 3 la led OK 
const int RECV_PIN = 2; 
IRrecv irrecv(RECV_PIN); 
decode_results messageRecu;
IRsend irLed;


void setup(){  
  Serial.begin(9600); 
  irrecv.enableIRIn();
  irrecv.blink13(true);
  
} void loop() {
  
  joysticx = analogRead(A0);
  joysticy = analogRead(A1);
  
  
  x = map(joysticx, 0, 1023, 0, 10);
  y = map(joysticy, 0, 1023, 0, 10);
      
      if(x > 6)
    {
      irLed.sendRC5(0x46c7 ,32);
      
    }
      if(x < 4)
    { 

      for(int n = 0; n <= 50; n++){
      irLed.sendRC5(0x4c ,n);
     delay(50);
      }
      
    }
    
      }

        
