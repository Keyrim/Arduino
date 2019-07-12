#include <SoftwareSerial.h>
//pin 11 = txd
//pin 10 = rxd

SoftwareSerial HC06(11,10);
 const char DOUT_LED = 2;
 String messageRecu;

void setup() {
   Serial.begin(9600);
   HC06.begin(9600);  
   pinMode(DOUT_LED, OUTPUT);
   digitalWrite(DOUT_LED, LOW);
 }
  
 void loop()
 {
     while(HC06.available())
     {
       delay(3);
       char c = HC06.read();
       messageRecu += c;
     }
     if (messageRecu.length() >0)
     {
       Serial.println(messageRecu);
       if (messageRecu == "LED:1")     
         {digitalWrite(DOUT_LED, HIGH);}
       if (messageRecu == "LED:0")
         {digitalWrite(DOUT_LED, LOW);}
       messageRecu="";
     }
 }

