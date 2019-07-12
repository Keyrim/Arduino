
#include <LiquidCrystal.h>
LiquidCrystal lcd(10, 11, 5, 4, 3, 2);
void setup() {
  lcd.begin(16,2);

}

void loop() {

 lcd.setCursor(0,0);
 lcd.print("Coucou");
delay(1000);

}
