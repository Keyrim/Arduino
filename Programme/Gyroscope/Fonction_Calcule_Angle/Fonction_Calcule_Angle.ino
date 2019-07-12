//branchement
//A4 = SDA
//A5 = SCL
#include<Wire.h>                       //introduction de la librairy destinné au gyroscope
const int MPU=0x68;                    //adresse du gyro
float X =0, Y = 0, Z =0, acX, acY, acZ;
int mpuX, mpuY, mpuZ ,mpuAcX, mpuAcY, mpuAcZ ;
int GyXCal, GyYCal, GyZCal ;
int temp ;

void angle(){  

   



    Wire.beginTransmission(MPU);                                   //Start communication with the gyro.
    Wire.write(0x3B);                                                       //Start reading @ register 43h and auto increment with every read.
    Wire.endTransmission();                                                 //End the transmission.
    Wire.requestFrom(MPU,14);                                      //Request 14 bytes from the gyro.    
    while(Wire.available() < 14);                                           //Wait until the 14 bytes are received.
    mpuX = Wire.read()<<8|Wire.read();                                      //Add the low and high byte to the acc_x variable.
    mpuY = Wire.read()<<8|Wire.read();                                      //Add the low and high byte to the acc_y variable.
    mpuZ = Wire.read()<<8|Wire.read();                                      //Add the low and high byte to the acc_z variable.
    temp = Wire.read()<<8|Wire.read();                               //Add the low and high byte to the temperature variable.
    mpuAcX = Wire.read()<<8|Wire.read();                                    //Read high and low part of the angular data.
    mpuAcY = Wire.read()<<8|Wire.read();                                    //Read high and low part of the angular data.
    mpuAcZ = Wire.read()<<8|Wire.read();                                    //Read high and low part of the angular data.
  
    }

void calibration ()
{
    for(int n =0; n < 2000; n ++ )
    {   
        angle();
        GyYCal += mpuY ;
        GyZCal += mpuZ ;
        GyXCal += mpuX ;
    }
    GyYCal /= 2000 ;
    GyZCal /= 2000 ;
    GyXCal /= 2000 ;
}

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
  //calibration();
}

void loop()
{
    angle();
    /*X += (mpuX - GyXCal) ;
    Y += (mpuY - GyYCal) ;
    Z += (mpuZ - GyZCal) ;*/
    Serial.println(mpuX);
    delay(100);
}


