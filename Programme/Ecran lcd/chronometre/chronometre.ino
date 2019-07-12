
long duration, distance = 0;

int x = 1000;   
long chronoseconde = x ;
long temps = 0 ;

#include <LiquidCrystal.h>     
LiquidCrystal lcd(10, 11, 9, 8, 7, 6);

#define trigPin 13  //Trig Ultrasons (sortie)
#define echoPin 12  //Echo Ultrasons (entrée)

void setup() {

  lcd.begin(16,2);
  
  Serial.begin (9600);  
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  
}

void loop() {

 temps = millis() ;
  lcd.setCursor(6,0);
      lcd.println("secondes");
      lcd.setCursor(0,0);
      lcd.println(temps / 1000);
      
      lcd.setCursor(0,1);
      lcd.println((temps / 1000) / 60 );
      lcd.setCursor(6,1);
      lcd.println("minutes");
 
 //if(distance > 0 && distance <= 300){
  
  
if(millis() - temps >= 1000){
    temps = millis() ;
    
    
     
      
 if( -- chronoseconde <= 0 ){
       
     
        digitalWrite(2, HIGH);
        //digitalWrite(2, LOW);
        
         }
       
          
        
        
   // }
 
     
    
 }
   
    
 
  
  
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Trig déclenché 10ms sur HIGH
  digitalWrite(trigPin, LOW);
  
  // Calcul de l'écho
  duration = pulseIn(echoPin, HIGH);
  // Distance proportionnelle à la durée de sortie
  distance = duration*340/(2*10000);  //Vitesse du son théorique 
  

 
   
}



