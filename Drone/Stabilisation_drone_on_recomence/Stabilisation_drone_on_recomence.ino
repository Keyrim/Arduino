//branchement
//A4 = SDA
//A5 = SCL
#include<Wire.h>                       //introduction de la librairy destinné au gyroscope
const int MPU=0x68;                    //adresse du gyro
float rollEreur, pitchEreur ;
float AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ,AcTotal;
float rollPrece =0 , pitchPrece =0 , yawPrece =0;
float GyXCal =0, GyYCal=0, GyZCal=0 ; 
float AcXangle , AcYangle, pitch, roll, yaw, finalPitch ,finalRoll ;
float rollErreur, pitchErreur, integralPitch, integralRoll ;
bool accSet = false ; 
unsigned long  loopTimer ;

int temp ;
#define pinMoteur1 2
#define pinMoteur2 3
#define pinMoteur3 4
#define pinMoteur4 5
#define pinChanel1 6
#define pinChanel2 7
#define pinChanel3 8
#define pinChanel4 9
int puissanceMoteur1, puissanceMoteur2, puissanceMoteur3, puissanceMoteur4, compensationX, compensationY;
unsigned long timer, timerMoteur ;
int chanel3,chanel2 ,chanel1, chanel4 ;
const float D = 0.05, P= 0.05, I= 0 ;




void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  for(int n = 0 ; n<1000; n++){
    angle();
    GyXCal += GyX ;
    GyYCal += GyY ;
    GyZCal += GyZ ;
  }
  GyXCal /= 1000 ;
  GyYCal /= 1000 ;
  GyZCal /= 1000 ;
  loopTimer = micros();

}

void loop()
{
    angle();
    chanel3 = pulseIn(pinChanel1, HIGH);
    chanel3 = pulseIn(pinChanel2, HIGH);
    chanel3 = pulseIn(pinChanel3, HIGH);
    chanel3 = pulseIn(pinChanel4, HIGH);
    rollErreur = (chanel1-1000) / 5.55556 - finalRoll ;
    pitchErreur = (chanel2-1000)/5.55556 - finalPitch ;
    compensationX = pitchErreur * P + integralPitch * I + D * (pitchErreur - pitchPrece);
    compensationY = rollErreur * P + integralRoll * I + D * (rollErreur - rollPrece);

    rollPrece = rollErreur;
    pitchPrece = pitchErreur;
    yawPrece = yaw ;


    //attributions puissance moteur
    puissanceMoteur1 = chanel3 + compensationX + compensationY ;
    puissanceMoteur2 = chanel3 - compensationX + compensationY ;
    puissanceMoteur3 = chanel3 - compensationX - compensationY ;
    puissanceMoteur4 = chanel3 + compensationX - compensationY ;


    digitalWrite(pinMoteur1, HIGH);
    digitalWrite(pinMoteur2, HIGH);
    digitalWrite(pinMoteur3, HIGH);
    digitalWrite(pinMoteur4, HIGH);
    timerMoteur = micros () ;
    while(digitalRead(pinMoteur4)&&digitalRead(pinMoteur3)&&digitalRead(pinMoteur2)&&digitalRead(pinMoteur1))
    {
        if(micros() >= timerMoteur + puissanceMoteur1)digitalWrite(pinMoteur1, LOW);
        if(micros() >= timerMoteur + puissanceMoteur2)digitalWrite(pinMoteur2, LOW);
        if(micros() >= timerMoteur + puissanceMoteur3)digitalWrite(pinMoteur3, LOW);
        if(micros() >= timerMoteur + puissanceMoteur4)digitalWrite(pinMoteur4, LOW);
    }
    
    Serial.print(puissanceMoteur1);
    Serial.print("rr");
    Serial.print(puissanceMoteur2);
    Serial.print("rr");
    Serial.print(puissanceMoteur3);
    Serial.print("rr");
    Serial.println(puissanceMoteur4);


}
void angle(){  

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
  AcXangle += 10.5;
  AcYangle +=  0.75;
  if(accSet){
    pitch = pitch * 0.9 + AcXangle*0.1 ;
    roll = roll * 0.9 + AcYangle*0.1 ;    
  }
  else {
    accSet = true ;
    pitch = AcXangle ;
    roll = AcYangle ;
  }
  finalPitch = finalPitch *0.8 + pitch * 0.2 ;
  finalRoll  = finalRoll  *0.8 + roll  * 0.2 ;
    }