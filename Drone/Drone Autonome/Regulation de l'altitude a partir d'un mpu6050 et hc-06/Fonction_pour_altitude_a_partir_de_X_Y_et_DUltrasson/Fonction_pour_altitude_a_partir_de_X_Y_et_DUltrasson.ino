#define trigPin 13  //Trig Ultrasons (sortie)
#define echoPin 12  //Echo Ultrasons (entrée)
#include<Wire.h>                       //introduction de la librairy destinné au gyroscope
const int MPU=0x68;                    //adresse du gyro
float distanceAuSol ;
float angleX,  angleY ;
  float distanceUltrasson;  
float fonctionDistanceAuSol(){
  float tanX, tanY ;
  int X=0, Y=0 ;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
  distanceUltrasson = pulseIn(echoPin, HIGH)/ 58.82 ; 
     
    Wire.beginTransmission(MPU);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,6,true); // request a total of 6 registers
    Y=Wire.read()<<8|Wire.read() ; // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    X=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L) 
  if(X <0) X*= -1 ;
  if(Y <0) Y*= -1 ;
  
  angleX = X * 0.00533;
  angleY = Y * 0.00533;
  tanX = tan(angleX);
  tanY = tan(angleY);
  distanceAuSol = pow(tanX, 2) + pow(tanY, 2) + 1 ;
  distanceAuSol = pow(distanceUltrasson, 2) / distanceAuSol ;
  distanceAuSol = sqrt(distanceAuSol);
  return distanceAuSol ;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée

}

void loop() {
 // Serial.println(fonctionDistanceAuSol());
 fonctionDistanceAuSol();
  Serial.print(distanceUltrasson);
  Serial.print("  ");
  Serial.println(angleY);
  delay(100);
}




















