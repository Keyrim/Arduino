#define sortie1  3
#define sortie2  4
#define sortie3  5
#define sortie4  6
#define sortie5  7
#include <Servo.h>  //ajoute la librari servo pour la comabde des moteurs 
Servo C1;     
Servo C2;     
Servo C3;     
Servo C4;     
Servo C5;


int signal1, signal2, signal3, signal4, signal5;
unsigned long timerLoop, signalTimer, timer, loopFrequence;
byte last_channel_1, last_channel_2, last_channel_3, last_channel_4;
unsigned long timer_1, timer_2, timer_3, timer_4, temps;

void setup() {
  Serial.begin(9600);
  PCICR |= (1 << PCIE0);    
  PCMSK0 |= (1 << PCINT0);  
  PCMSK0 |= (1 << PCINT1);  
  PCMSK0 |= (1 << PCINT2);  
  PCMSK0 |= (1 << PCINT3);   
  pinMode(sortie1, OUTPUT);
  pinMode(sortie2, OUTPUT);
  pinMode(sortie3, OUTPUT);
  pinMode(sortie4, OUTPUT);
  pinMode(sortie5, OUTPUT);
  timerLoop = micros();
  Serial.print(timerLoop);
  C1.attach(sortie1);
  C2.attach(sortie2);
  C3.attach(sortie3);
  C4.attach(sortie4);
  C5.attach(sortie5);
}

void loop() {
  timerLoop=micros();

  C1.writeMicroseconds(signal1);
  C2.writeMicroseconds(signal2);
  C3.writeMicroseconds(signal3);
  C4.writeMicroseconds(signal4);
  C5.writeMicroseconds(signal5);
 
  
  /*
  Serial.print(signal1);
  Serial.print(" ");
  Serial.print(signal2);
  Serial.print(" ");
  Serial.print(signal3);
  Serial.print(" ");
  Serial.println(signal4);*/
  Serial.println(micros() - timerLoop);
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









