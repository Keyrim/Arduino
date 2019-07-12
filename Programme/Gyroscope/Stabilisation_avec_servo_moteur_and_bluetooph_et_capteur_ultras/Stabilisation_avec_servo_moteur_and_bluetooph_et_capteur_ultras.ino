
#include<Wire.h>
const int MPU=0x68; 
int16_t AcX,AcY;
int X, Y;

#include <Servo.h>
Servo SMoteur;  // create servo object to control a servo

#define trigPin 7  //Trig Ultrasons (sortie)
#define echoPin 6  //Echo Ultrasons (entrée)

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

void calculeAngle(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true); // request a total of 6 registers
  AcX=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  //Serial.print("AcX = ")    ;
  Serial.println(X);
 // Serial.print(" \t | AcY = ") ; Serial.println(Y);
  Y = map(AcX, -16000, 16700, 90, 0);
  X = map(AcY, -16500, 16200, 0, 360);
}

#include <SoftwareSerial.h>
//pin 11 = txd
//pin 10 = rxd
SoftwareSerial Bluecom(13,12);

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  SMoteur.attach(9);
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
  Bluecom.begin(9600);
  
}

void loop(){
 calculeAngle();
 SMoteur.write(Y*2);
 calculDistance();
 Bluecom.print("La distance est de : ");
 Bluecom.print(distance);
 Bluecom.println(" centimetre.");
 delay(100);

 
}

