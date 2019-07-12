//programme censer permettre de renvoyer les signaux du recepteur de la telecomadne
#include <Servo.h>
#include<Wire.h>                       //introduction de la librairy destinné au gyroscope
#define pinChIn6 9
#define pinChIn5 10
#define pinChOut5 8
#define pinGimbal 7
Servo channel5;
Servo gimbal;
unsigned int signalCh5(0), signalCh6(0) ;
const int MPU=0x68;                    //adresse du gyro
int  X, Y,  corectionY, signalGimbal;


void angle(){
  int compteur(0);
  for(int n = 0 ; n < 10 ; n++){
    Wire.beginTransmission(MPU);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,6,true); // request a total of 6 registers
    Y=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    X=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    Y =( Y / 100) + corectionY ;
    compteur += Y ;
  }  Y = compteur / 10 ;
}
void lecturSignal(){
  signalCh5 = pulseIn(pinChIn5, HIGH);
  signalCh6 = pulseIn(pinChIn6, HIGH);
}

void setup() { 
  Serial.begin(9600);
  channel5.attach(pinChOut5);
  gimbal.attach(pinGimbal);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pinMode(pinChIn5, INPUT);
  pinMode(pinChIn6, INPUT); 
  int compteurX(0), compteurY(0) ;
  for(int n = 0 ; n < 100 ; n++){
    Wire.beginTransmission(MPU);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,6,true); // request a total of 6 registers
    Y=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    X=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    Y = Y / 100 ;
    compteurY += Y ;
  }
  corectionY = compteurY / 100 ;
}

void loop() {
  angle();
  //lecturSignal(); 
  Serial.println(Y);
  signalGimbal = (Y/2) * -1 + 60 ; 
  gimbal.write(signalGimbal);
  channel5.writeMicroseconds(2000);
  
  

}











