#include<Wire.h>
#include "RunningAverage.h"
const int MPU=0x68;  // I2C address of the MPU-6050

int angle(bool x)
{
  float AcX,AcY,AcZ,GyX,GyY,GyZ,AcTotal, Tmp;
  float AcXangle , AcYangle;
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x3B);                                                    //Send the requested starting register
  Wire.endTransmission();                                              //End the transmission
  Wire.requestFrom(0x68,6);                                           //Request 14 bytes from the MPU-6050
  while(Wire.available() < 6);                                        //Wait until all the bytes are received
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  /*Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)*/
  AcTotal = sqrt(AcX*AcX + AcZ*AcZ + AcY*AcY);
  AcXangle = asin(AcX/AcTotal) * 57.296 ;
  AcYangle = asin(AcY/AcTotal) * -57.296 ;
  //AcXangle += 10.5;
  //AcYangle +=  0.75;
  if(x)return AcXangle;
  else return AcYangle;
}
const unsigned char n = 50 ;
unsigned char i = 0;
int valeursX[n];
int valeursY[n];
float sommeY=0;
float sommeX=0;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  
}


void loop(){
  sommeY-=valeursY[i];
  sommeX-=valeursX[i];
  valeursX[i] = angle(true);
  valeursY[i] = angle(false);  
  sommeX+= valeursX[i];
  sommeY+= valeursY[i];
  i++;
  if(i >= n ) i = 0 ;
  if(i%3==0){
    Serial.print(sommeX/n);
    Serial.print("  ");
    Serial.println(sommeY/n);
  }
  delay(3);
  
  
  
  




  
}
