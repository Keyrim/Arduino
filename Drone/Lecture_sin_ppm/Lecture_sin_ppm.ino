bool etatSignal [4];
unsigned long curentTime,timer [4] ;
int signal [4] ;


void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}
 
void setup ()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);  // LED
  digitalWrite(13, HIGH);
  pciSetup(10);
  pciSetup(8);
  pciSetup(9);
  pciSetup(11);

}

void loop ()
{
    Serial.print(signal[0]);
    Serial.print("   ");
    Serial.print(signal[1]);
    Serial.print("   ");
    Serial.print(signal[2]);
    Serial.print("   ");
    Serial.println(signal[3]);
    delay(100);

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
