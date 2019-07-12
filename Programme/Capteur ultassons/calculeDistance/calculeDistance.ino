//**********************************************************
//  Capteur de distance à ultrasons HC-SR04 avec Arduino Uno
//  TipTopBoards.com  06 01 2014  Rolland
//  Càabler +5V et GND du détecteur sur l'arduino
//
// Trig -> pin 13
// Echo -> pin 12
// Led verte + 470R  -> pin 10
// Led rouge + 470R  -> pin 11
// Les leds s'allument selon la distance trop près / trop loin
//**********************************************************


/* branchement :
 *    capteur de distance:
 *       trig => pin 13
 *       echo => pin 12 
 *    buzzer =>  pin n
 */

 
#define trigPin 13  //Trig Ultrasons (sortie)
#define echoPin 12  //Echo Ultrasons (entrée)
#define ledVerte 11      //Led verte
#define ledRouge 10     //Led rouge

long duration, distance;

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
  Serial.begin (115200);  
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
  
}

void loop() {
  
  calculDistance();
  
  //Hors de portée (duration)
  if( distance <= 0){  
    //Serial.print(duration);
    Serial.println("Hors de portee");
  }
  else {
    Serial.print(distance);
    Serial.print(" cm ");
    Serial.print(duration);
    Serial.println(" ms");
  }
  delay(100);
}
