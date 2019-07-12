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
#define trigPin 13  //Trig Ultrasons (sortie)
#define echoPin 12  //Echo Ultrasons (entrée)
#define ledVerte 11      //Led verte
#define ledRouge 10     //Led rouge

void setup() {
  Serial.begin (9600);  
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
 
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Trig déclenché 10ms sur HIGH
  digitalWrite(trigPin, LOW);
  
  // Calcul de l'écho
  duration = pulseIn(echoPin, HIGH);
  // Distance proportionnelle à la durée de sortie
  distance = duration*340/(2*10000);  //Vitesse du son théorique
 if(distance <20) {
    digitalWrite(11,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(9,LOW);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);
   
 }
  
 if(distance > 15) {
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);
  
    
     
  }
   if(distance > 20) {
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);
  
     
  }
   if(distance > 25) {
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(7,LOW);

     
  }
   if(distance > 30) {
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(7,HIGH);
    
    
     
  }
   if(distance > 35) {
    digitalWrite(11,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(7,HIGH);
    
  
     
  }
    delay(50);
    
   

 if(distance > 40 ) {   //Trop loin
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    digitalWrite(9,LOW);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);
    

   
  }
 
 
     
  


  
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
  delay(1000);
}
