#include <LiquidCrystal.h>
float temp;




void setup(){

Serial.begin(9600);
}


void loop(){
temp = ((analogRead(0) * 1000) - 500) / 10;



Serial.print(analogRead(0));
Serial.print("    ");
Serial.print("Temp: ");
Serial.println(temp);

delay(1000);
}

