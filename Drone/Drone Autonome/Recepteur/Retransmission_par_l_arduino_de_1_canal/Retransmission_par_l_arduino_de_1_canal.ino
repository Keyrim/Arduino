#define pinGazIn 6
#define pinGazOut 7
#include <Servo.h>
Servo gaz;
unsigned int signalGaz;
unsigned long timerLoop(0), timerGaz(0);


void setup() {
  Serial.begin(115200);
  pinMode(pinGazIn, INPUT);
  gaz.attach(pinGazOut);

}

void loop() {
  signalGaz = pulseIn(pinGazIn, HIGH);
  gaz.writeMicroseconds(signalGaz);
  Serial.println(analogRead(A0));

}
