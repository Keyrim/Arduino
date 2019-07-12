bool etatSignal [4];
unsigned long curentTime,timer [4] ;
int signal [4] ;
int moteur [4] ;
unsigned long timerMoteur, timerMoteur2, timerLoopFrequence ;
int compensationRoll = 0, compensationPitch = 0;
#include<Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050
float AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ,AcTotal;
float GyXCal =0, GyYCal=0, GyZCal=0 ; 
float AcXangle , AcYangle, pitch, roll, finalPitch ,finalRoll ;
bool accSet = false ; 

void angle()
{
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x3B);                                                    //Send the requested starting register
  Wire.endTransmission();                                              //End the transmission
  Wire.requestFrom(0x68,14);                                           //Request 14 bytes from the MPU-6050
  while(Wire.available() < 14);                                        //Wait until all the bytes are received
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  GyX -= GyXCal ;
  GyY -= GyYCal ;
  GyZ -= GyZCal ;
  pitch += GyX * 0.0000611 ;
  roll += GyY * 0.0000611 ;
  AcTotal = sqrt(AcX*AcX + AcZ*AcZ + AcY*AcY);
  AcXangle = asin(AcX/AcTotal) * 57.296 ;
  AcYangle = asin(AcY/AcTotal) * -57.296 ;
  //AcXangle += 10.5;
  //AcYangle +=  0.75;
  if(accSet){
    pitch = pitch * 0.99 + AcXangle*0.01 ;
    roll = roll * 0.99 + AcYangle*0.01 ;    
  }
  else {
    accSet = true ;
    pitch = AcXangle ;
    roll = AcYangle ;
  }
  //finalPitch = finalPitch *0.8 + pitch * 0.2 ;
  //finalRoll  = finalRoll  *0.8 + roll  * 0.2 ;
   finalPitch = pitch ;
   finalRoll = roll ; 
}

void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}
void affichage(){
    Serial.print(finalRoll);
    Serial.print("   ");
    Serial.print(finalPitch);
    Serial.print("   ");
    Serial.print(signal[2]);
    Serial.print("   ");
    Serial.println(moteur[0]);
}

 
void setup ()
{
  Serial.begin(115200);
  pinMode(13,OUTPUT);  // LED
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  digitalWrite(13, HIGH);
  for(int n = 0 ; n<1000; n++){
    angle();
    GyXCal += GyX ;
    GyYCal += GyY ;
    GyZCal += GyZ ;
  }
  GyXCal /= 1000 ;
  GyYCal /= 1000 ;
  GyZCal /= 1000 ;
  pciSetup(10);
  pciSetup(8);
  pciSetup(9);
  pciSetup(11);
  timerLoopFrequence = micros();
  
}

void loop ()
{
  if(signal[2] > 1050){
    angle();
    compensationRoll = finalRoll*10  ; 
    compensationPitch = finalPitch*10 ;
    moteur[0]= signal[2] + compensationRoll + compensationPitch ;
    moteur[1]= signal[2] - compensationRoll + compensationPitch ;
    moteur[2]= signal[2] - compensationRoll - compensationPitch ;
    moteur[3]= signal[2] + compensationRoll - compensationPitch ;
    for (int i = 0; i <4 ; i ++){
      if(moteur[i] < 1000) moteur[i] = 1000;
      if(moteur[i] > 2000) moteur[i] = 2000;
    }
  }
  else 
    for (int i = 0; i <4 ; i ++){
      moteur[i] = 1000;
    }
  
    
    
    PORTD |= B11110000;                                                       
    timerMoteur = micros();
    while(PORTD >= 16){
      timerMoteur2 = micros();
      if(timerMoteur2 >= timerMoteur + moteur[0])PORTD &= B11101111; 
      if(timerMoteur2 >= timerMoteur + moteur[1])PORTD &= B11011111; 
      if(timerMoteur2 >= timerMoteur + moteur[2])PORTD &= B10111111; 
      if(timerMoteur2 >= timerMoteur + moteur[3])PORTD &= B01111111; 
    }
    affichage();
    while(micros()<timerLoopFrequence+4000);
    timerLoopFrequence = micros();
}


ISR (PCINT0_vect) // handle pin change interrupt for D8 to D13 here
 {    curentTime = micros();

 for(int n=0 ; n <4; n++){
     if(digitalRead(n+8)==1){
      if(etatSignal[n]==0){
        etatSignal[n] = 1 ;
        timer[n] = curentTime ;
      }
     }
     else if(etatSignal[n]==1){
      etatSignal[n] = 0 ;
      signal[n] = micros()-timer[n] ;
     }
 } 
 }
