//branchement
//A4 = SDA
//A5 = SCL
#include<Wire.h>                       //introduction de la librairy destinné au gyroscope
const int MPU=0x68;                    //adresse du gyro
long X(0), Y(0), Z(0) ,gX(0), gY(0), gZ(0), cX(0), cY(0), cZ(0);
unsigned long tempsAcuelle (0);

void angle(){
  Wire.beginTransmission(MPU);                        //Start communication with the gyro
  Wire.write(0x43);                                            //Start reading @ register 43h and auto increment with every read
  Wire.endTransmission();                                      //End the transmission
  Wire.requestFrom(MPU,6,true); // request a total of 6 registers
  gX = Wire.read()<<8|Wire.read();                   //Read high and low part of the angular data
  gY = Wire.read()<<8|Wire.read();                   //Read high and low part of the angular data
  gZ = Wire.read()<<8|Wire.read();                   //Read high and low part of the angular data 
  X += (gX /1000) - cX;
  Y += (gY /1000) - cY;
  Z += (gZ /1000) - cZ;
   
}
void setupGyro(){
    Wire.beginTransmission(MPU);                        //Start communication with the address found during search.
    Wire.write(0x6B);                                            //We want to write to the PWR_MGMT_1 register (6B hex)
    Wire.write(0x00);                                            //Set the register bits as 00000000 to activate the gyro
    Wire.endTransmission();                                      //End the transmission with the gyro.    
    Wire.beginTransmission(MPU);                        //Start communication with the address found during search.
    Wire.write(0x1B);                                            //We want to write to the GYRO_CONFIG register (1B hex)
    Wire.write(0x08);                                            //Set the register bits as 00001000 (500dps full scale)
    Wire.endTransmission();                                      //End the transmission with the gyro  //Let's perform a random register check to see if the values are written correct
    Wire.beginTransmission(MPU);                        //Start communication with the address found during search
    Wire.write(0x1B);                                            //Start reading @ register 0x1B
    Wire.endTransmission();                                      //End the transmission
    Wire.requestFrom(MPU, 1);                           //Request 1 bytes from the gyro
    while(Wire.available() < 1);                                 //Wait until the 6 bytes are received
    if(Wire.read() != 0x08){                                     //Check if the value is 0x08
      digitalWrite(12,HIGH);                                     //Turn on the warning led
      while(1)delay(10);                                         //Stay in this loop for ever
    }
    
    Wire.beginTransmission(MPU);                        //Start communication with the address found during search
    Wire.write(0x1A);                                            //We want to write to the GYRO_CONFIG register (1B hex)
    Wire.write(0x03);                                            //Set the register bits as 00001000 (500dps full scale)
    Wire.endTransmission();                                      //End the transmission with the gyro    

}
void calibrationGyro(){
  Serial.print("CalibrationGyro");
  long sommeX(0), sommeY(0), sommeZ(0);
  for(int tour(0); tour < 2000; tour++){
    angle();
    sommeX += X ;
    sommeY += Y ;
    sommeZ += Z ;
    delay(1);
    if(tour%50 == 0)Serial.print(".");
  }
  cX = sommeX / 2000;
  cY = sommeY / 2000;
  cZ = sommeZ / 2000; 
  Serial.println(); 
  Serial.print(cY);
  Serial.print("   ");
  Serial.print(cX);
  Serial.print("   ");
  Serial.println(cZ); 
}
void setup(){
  Serial.begin(9600);
  setupGyro();
  calibrationGyro();

}

void loop(){
  angle();
  Serial.print(Y);
  Serial.print("   ");
  Serial.print(X);
  Serial.print("   ");
  Serial.println(Z); 
  delay(10); 
}













