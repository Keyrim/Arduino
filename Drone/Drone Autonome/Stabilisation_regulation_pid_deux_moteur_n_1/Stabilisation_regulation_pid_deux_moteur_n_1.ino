#define sortie1  6
#define sortie2  7
#define entrer5  12
//branchement
//A4 = SDA
//A5 = SCL
#include<Wire.h>                       //introduction de la librairy destinné au gyroscope
const int MPU=0x68;                    //adresse du gyro
long X, Y;
#include <Servo.h>  //ajoute la librari servo pour la comabde des moteurs 
Servo C1;     //defini un moteur "M1"
Servo C2;     //defini un moteur "M2"
int16_t AcX,AcY;      // declare les varible necessaire au gyroscope 
float signal1, signal2, signal3, signal4, signal5, consigne ;
int puissanceM1, puissanceM2;
unsigned long timerLoop, signalTimer, timer, loopFrequence;
byte last_channel_1, last_channel_2, last_channel_3, last_channel_4;
unsigned long timer_1, timer_2, timer_3, timer_4, temps;


void angle(){
  X=0;
  for(int n=0; n<100;n++)
  {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,6,true); // request a total of 6 registers
    AcY=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AcX=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    X+=AcX ;
  }
    Y = AcY  ;
    X = X /100  ;
  
}



void setup() {
  Serial.begin(9600);
  PCICR |= (1 << PCIE0);    
  PCMSK0 |= (1 << PCINT0);  
  PCMSK0 |= (1 << PCINT1);  
  PCMSK0 |= (1 << PCINT2);  
  PCMSK0 |= (1 << PCINT3);   
  pinMode(sortie1, OUTPUT);
  pinMode(sortie2, OUTPUT);
  pinMode(entrer5, INPUT);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  timerLoop = micros();
  C1.attach(sortie1);
  C2.attach(sortie2);
}

int ecartX = 0 , ecartXPrecedent = 0 , D = 0, P = 0, I=0;
float kD  = 0.02, kP = 0.003, kI = 0.00;

void loop() {

  
    //quand x < 0 , m2 trpo faible par raport a m1
    angle();
    consigne = (signal4-1500)*20;
    ecartX = X - consigne ;
    P = ecartX * kP ;  
    I += ecartX * kI ; 
    D = (ecartXPrecedent - ecartX )*kD;
    puissanceM1 = signal3 + P -D;
    puissanceM2 = signal3 - P +D;
    puissanceM2=map(puissanceM2, 1000, 2000, 1000, 1810);
    verifPuissanceMoteur();
    C1.writeMicroseconds(puissanceM1);
    C2.writeMicroseconds(puissanceM2);
    ecartXPrecedent = ecartX;
    Serial.println(signal3);
  
}
void verifPuissanceMoteur(){
  if(puissanceM2 < 0)puissanceM2 = 0;
  if(puissanceM1 < 0)puissanceM1 = 0;
  if(puissanceM2 > 2000)puissanceM2 = 2000;
  if(puissanceM1 > 2000)puissanceM1 = 2000;  
}

ISR(PCINT0_vect){
  //Channel 1=========================================
  if(last_channel_1 == 0 && PINB & B00000001 ){         //Input 8 changed from 0 to 1
    last_channel_1 = 1;                                 //Remember current input state
    timer_1 = micros();                                 //Set timer_1 to micros()
  }
  else if(last_channel_1 == 1 && !(PINB & B00000001)){  //Input 8 changed from 1 to 0
    last_channel_1 = 0;                                 //Remember current input state
    signal1= micros() - timer_1;      //Channel 1 is micros() - timer_1
  }
  //Channel 2=========================================
  if(last_channel_2 == 0 && PINB & B00000010 ){         //Input 9 changed from 0 to 1
    last_channel_2 = 1;                                 //Remember current input state
    timer_2 = micros();                                 //Set timer_2 to micros()
  }
  else if(last_channel_2 == 1 && !(PINB & B00000010)){  //Input 9 changed from 1 to 0
    last_channel_2 = 0;                                 //Remember current input state
    signal2= micros() - timer_2;      //Channel 2 is micros() - timer_2
  }
  //Channel 3=========================================
  if(last_channel_3 == 0 && PINB & B00000100 ){         //Input 10 changed from 0 to 1
    last_channel_3 = 1;                                 //Remember current input state
    timer_3 = micros();                                 //Set timer_3 to micros()
  }
  else if(last_channel_3 == 1 && !(PINB & B00000100)){  //Input 10 changed from 1 to 0
    last_channel_3 = 0;                                 //Remember current input state
    signal3 = micros() - timer_3;      //Channel 3 is micros() - timer_3
  }
  //Channel 4=========================================
  if(last_channel_4 == 0 && PINB & B00001000 ){         //Input 11 changed from 0 to 1
    last_channel_4 = 1;                                 //Remember current input state
    timer_4 = micros();                                 //Set timer_4 to micros()
  }
  else if(last_channel_4 == 1 && !(PINB & B00001000)){  //Input 11 changed from 1 to 0
    last_channel_4 = 0;                                 //Remember current input state
    signal4 = micros() - timer_4;      //Channel 4 is micros() - timer_4
  }
}









