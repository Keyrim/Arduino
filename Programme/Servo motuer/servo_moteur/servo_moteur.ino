#include <Servo.h>
  
 Servo monServo;  
  
 const char AN_POTENTIOMETRE = 0;  //sortie du joystick
 
int positionDuServo = 0;

  
 void setup()
 {
   Serial.begin(9600);
   monServo.attach(9); 
   monServo.write(180); 
   delay(1000);  
 }
  
 void loop()
 {
   positionDuServo = analogRead(AN_POTENTIOMETRE);           
   positionDuServo = map(positionDuServo, 0, 1023, 0, 180);     
   monServo.write(50);
    
                              
 }






