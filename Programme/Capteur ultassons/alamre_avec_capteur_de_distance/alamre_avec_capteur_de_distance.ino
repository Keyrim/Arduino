/* programme permetant de declencher une alarme
 *si le capteur ultrassons detecte quelquechose
 *
 *  branchement :
 *    capteur de distance:
 *       trig => pin 13
 *       echo => pin 12 
 *    buzzer =>  pin n
 */


#define trigPin 13  //Trig Ultrasons (sortie)
#define echoPin 12  //Echo Ultrasons (entrée)

#include <avr/wdt.h>


long duration, distance;
int n = 10;
int x = 1000 ;     //duré entre chaque alerte 

void reset()
{
  asm volatile ("  jmp 0"); 
} 


void calculDistance(){
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

void setup() {
  Serial.begin (9600);  
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
  pinMode(n      , OUTPUT);  //Definition du pin de sortie du buzzer 5v 
  pinMode(10     , INPUT);
}

void loop() {
  
  
  
  calculDistance(); 
  Serial.println(distance);

  if(distance > 5 && distance < 100){  // si le capteur capte qqchose 

    while(digitalRead(11) == LOW){
      
       
      tone(n, 4000);
      delay(100);
      tone(n, 2000);
      delay(100);
    
    }
    
  noTone(10);

  }
  
}
















