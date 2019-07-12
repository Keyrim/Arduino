
//pin 13 = txd
//pin 12 = rxd

#include <SoftwareSerial.h>
SoftwareSerial BlueCom(13, 12);

int MessRecu;
int led ;
long tempsActu;
int mot;
int nombre;
int valeurPWM;
int PWMmoins;

int bonjour = 767;
int allumer = 754;
int eteindre = 848;
int toutallumer = 1214;
int touteteindre = 1308 ;
int chenillard = 1046;
int pwm = 340 ; 


void setup() {
for(int n = 0; n <=11; n++){
    pinMode(n, OUTPUT);
  }

 BlueCom.begin(9600);
 Serial.begin(9600);
 Serial.println();
  
  BlueCom.println();
  BlueCom.println("Bonjour ,je suis pret.");
  BlueCom.println();
  BlueCom.println();

}

void loop() {

    tempsActu = millis();
    mot = 0;
    nombre = 0;
    led = 0;
    MessRecu = BlueCom.read();
  
  if (MessRecu == 340)
   {
    while(millis() <= tempsActu + 3000){
       if (BlueCom.available()){
        BlueCom.println("enree valeur");
        BlueCom.println();
        BlueCom.println();
        MessRecu = BlueCom.read();
        PWMmoins = MessRecu - 48;
        PWMmoins = PWMmoins * 10;
        valeurPWM = valeurPWM + PWMmoins ;
       }
    }
     Serial.println(valeurPWM);
   }


else{
      digitalWrite(11, 1);
      delay(100);
      digitalWrite(11, 0);
      delay(100);
    }
}
