//This file is used to aply a filter to the raw data from the mpu 6050
#include <Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050

//raw data
int AcX, AcY, AcZ, GyX, GyY, GyZ;

void read_mpu()
{
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);       //Send the starting register (accelerometer)
    Wire.endTransmission();
    Wire.requestFrom(MPU, 6);
    while (Wire.available()< 6);
    AcX = Wire.read()<<8|Wire.read();
    AcY = Wire.read()<<8|Wire.read();
    AcZ = Wire.read()<<8|Wire.read();
    
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission();
    Wire.requestFrom(MPU, 4);
    while(Wire.available()< 4);
    GyX = Wire.read()<<8|Wire.read();
    GyY = Wire.read()<<8|Wire.read();


}

void setup()
{
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission();

    Serial.begin(9600);

}

void loop()
{

}