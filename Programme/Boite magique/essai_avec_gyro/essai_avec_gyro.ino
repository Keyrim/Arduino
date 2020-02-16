//pin 13 = txd
//pin 12 = rxd
#include <SoftwareSerial.h>
SoftwareSerial BlueCom(13, 12);

#include <Servo.h>
Servo monServo; 

#define trigPin 11  //Trig Ultrasons (sortie)
#define echoPin 10  //Echo Ultrasons (entrée)

#include<Wire.h>
const int MPU=0x68; // I2C address of the MPU-6050
int16_t AcX,AcY;
int X, Y;

void calculeAngle(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true); // request a total of 6 registers
  AcX=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  Y = map(AcX, -16000, 16700, 0, 360);
  X = map(AcY, -16500, 16200, 0, 360);
  BlueCom.print("AcX = ")       ; BlueCom.print(X);
  BlueCom.print(" \t AcY = ") ; BlueCom.println(Y);
  
}



long duration, distance;
char mot [250];
char messageRecu ;
byte i = 0;
String Mot ;
int nombre ;

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

void receptionLoop(){
  if(BlueCom.available()){
    
  while(messageRecu != '#'){
      
    
if(BlueCom.available()){
  
      messageRecu  = BlueCom.read();

      if(messageRecu != '#'){
      BlueCom.print(messageRecu);
      mot[i] = messageRecu ;
      i++ ;
      }
    }
    
  }

  

 mot[i] = 0 ;

 i = 0;
 Mot = mot ; 
 nombre = Mot.toInt();
 messageRecu = '}' ;
 BlueCom.println();
  
}
}

void reception(){
  
    
  while(messageRecu != '#'){
      
    
if(BlueCom.available()){
  
      messageRecu  = BlueCom.read();
     if(messageRecu != '#'){
      mot[i] = messageRecu ;
      i++ ;
      BlueCom.print(messageRecu);
      }
    }
    
  }
 mot[i] = 0 ;
 BlueCom.println();
 i = 0;
 Mot = mot ; 
 nombre = Mot.toInt();
 messageRecu = '}' ;
  
}


void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
 BlueCom.begin(9600);
 Serial.begin(9600);
 BlueCom.println();
 BlueCom.println("Bonjour, je suis pret");
 BlueCom.println();
 for(int l = 0; l<= 11; l++){
  pinMode(l, OUTPUT);
 }
   monServo.attach(9); 
   monServo.write(180);
   delay(1000);
   monServo.write(0); 
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
}

void loop() {
// sting : Mot
// int: nombre

receptionLoop();

if(Mot == "?"){
  BlueCom.println("Toutes les comande que je comprend sont :");
  BlueCom.println("Regler la tension de sortie une sortie PWM = Pwm");
  BlueCom.println("Calculer la distance de maniere continue(fonction distance) = Fd");
  BlueCom.println("Calculer l'angle(fonction angle) = Fa.");
  BlueCom.println("Stabilisation = Fg");
  BlueCom.println("Pour areter une fonction quelconque = fin");
}


                                                  //fin pour eteindre une lumiere 



if(Mot == "Pwm"){
  BlueCom.println("Sur quelle sortie voulez-vous effectuez la comande ?");
  reception();
  int led = nombre ;
  BlueCom.println("Quelle valeur souhaitez-vous apliquer a la sorti ?");
  reception();
  BlueCom.print("Comande effectuez sur la sortie ");
  BlueCom.print(led);
  BlueCom.print(" avc une valeur de ");
  BlueCom.println(nombre);
  analogWrite(led, nombre);
}

if(Mot == "Fd"){
 while(Mot != "fin"){
  calculDistance();
   if(distance < 310){
  BlueCom.print("La distance est de : ");
  BlueCom.print(distance);
  BlueCom.println(" centimetre.");
  receptionLoop();
   }
  else{
    BlueCom.println("Hors de porter");
   }
  delay(100);
   
 }
  BlueCom.println("Fin de la fonction.");
}

if(Mot == "Fs"){
 while(Mot != "fin"){
  BlueCom.print("Angle a \t");
  BlueCom.print(nombre);
  BlueCom.println(" \t degrer");
  monServo.write(nombre);
  delay(100);
  reception();
 }
  BlueCom.println("Fin de la fonction.");
}

if(Mot == "Fa"){
 while(Mot != "fin"){
  receptionLoop();
  calculeAngle();
  delay(50);
   
 }
  BlueCom.println("Fin de la fonction.");
}

if(Mot == "Fg"){
 while(Mot != "fin"){
  receptionLoop();
  calculeAngle();
  long positionDuServo = map(X, 0, 360, 0, 180);
  Serial.println(positionDuServo);
  monServo.write(positionDuServo);   
 }
  BlueCom.println("Fin de la fonction.");
}

Mot = "123456789" ;
}
