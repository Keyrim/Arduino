//This file is used to aply a filter to the raw data from the mpu 6050
//DataSheet of the mpu 
//https://store.invensense.com/datasheets/invensense/MPU-6050_DataSheet_V3%204.pdf
//Datasheet registre MPU 
//https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
#include <Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050
const int frequence = 250; //Frequence of the loop in hz
unsigned long loop_timer ; 
//raw data
float AcX, AcY, AcZ, GyX, GyY, GyZ;

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

    //Get the true raws values in g according to our setting
    AcZ /= 8192;
    AcX /= 8192;
    AcY /= 8192;
    
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission();
    Wire.requestFrom(MPU, 4);
    while(Wire.available()< 4);
    GyX = Wire.read()<<8|Wire.read();
    GyY = Wire.read()<<8|Wire.read();

    //Get the true raws values in deg/s according to our setting
    GyX /= 65.5;
    GyY /= 65.5;

}

void setup()
{
    // Wake up the mpu 
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission();

    //Set up the accelerometer
    //1g = 8192
    //+- 2g
    Wire.beginTransmission(MPU);
    Wire.write(0x1C);
    Wire.write(0x08);
    Wire.endTransmission();

    //Set up the gyroscope
    //1deg/s = 65.5 
    //+- 500
    Wire.beginTransmission(MPU);
    Wire.write(0x1B);
    Wire.write(0X08);
    Wire.endTransmission();    

    Serial.begin(115200);

}

void loop()
{
    read_mpu();

}