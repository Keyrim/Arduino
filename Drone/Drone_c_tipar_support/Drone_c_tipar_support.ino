//branchement
//A4 = SDA
//A5 = SCL
#include<Wire.h>                       //introduction de la librairy destinné au gyroscope
const int MPU=0x68;                    //adresse du gyro
float rollEreur, pitchEreur ;
float AcXangle , AcYangle, pitch, roll, yaw, finalPitch ,finalRoll ;
float rollErreur, pitchErreur, integralPitch, integralRoll ;
bool accSet = false ; 
unsigned long  loopTimer, lastTime ;

int temp ;
#define pinMoteur1 4
#define pinMoteur2 5
#define pinMoteur3 6
#define pinMoteur4 7
int puissanceMoteur1, puissanceMoteur2, puissanceMoteur3, puissanceMoteur4, compensationX, compensationY;
unsigned long  timerMoteur ;
const float D = 0.05, P= 0.05, I= 0 ;
bool etatSignal [4];
unsigned long escTimer, curentTime,timer [4] ;
int signal [4] ;

void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}


void setup()
{
  pciSetup(10);
  pciSetup(8);
  pciSetup(9);
  pciSetup(11);
  pinMode(pinMoteur1, OUTPUT);
  pinMode(pinMoteur2, OUTPUT);
  pinMode(pinMoteur3, OUTPUT);
  pinMode(pinMoteur4, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
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
  lastTime = micros();
  Serial.println("C tipar");
}

void loop()
{ 
    
   

    //attributions puissance moteur
    puissanceMoteur1 = signal[2] ;//+ compensationX + compensationY ;
    puissanceMoteur2 = signal[2] ;//- compensationX + compensationY ;
    puissanceMoteur3 = signal[2] ;//- compensationX - compensationY ;
    puissanceMoteur4 = signal[2] ;//+ compensationX - compensationY ;
    
    digitalWrite(pinMoteur1, HIGH);
    digitalWrite(pinMoteur2, HIGH);
    digitalWrite(pinMoteur3, HIGH);
    digitalWrite(pinMoteur4, HIGH);
    
    timerMoteur = micros () ;
    angle();
    while(PORTD >= 16)
    {
      escTimer = micros();
       if(escTimer >= timerMoteur + puissanceMoteur1)digitalWrite(pinMoteur1, LOW);
        if(escTimer >= timerMoteur + puissanceMoteur2)digitalWrite(pinMoteur2, LOW);
        if(escTimer >= timerMoteur + puissanceMoteur3)digitalWrite(pinMoteur3, LOW);
        if(escTimer >= timerMoteur + puissanceMoteur4)digitalWrite(pinMoteur4, LOW);
    }
    /*Serial.print(puissanceMoteur1);
    Serial.print("rr");
    Serial.print(puissanceMoteur2);
    Serial.print("rr");
    Serial.print(puissanceMoteur3);
    Serial.print("rr");
    Serial.println(puissanceMoteur4);*/
    Serial.println(micros()-lastTime);
    lastTime = micros();


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
