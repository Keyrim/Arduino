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




void receptionMot (){
  
  if (BlueCom.available())
   {


     

     
    while(millis() <= tempsActu + 4000){
       if (BlueCom.available()){
         MessRecu = BlueCom.read();
         mot = mot + MessRecu;
       }
    }
     Serial.println(mot);
   }
}

void receptionNombre (){

   while(millis() <= tempsActu + 8000){
       if (BlueCom.available()){
         MessRecu = BlueCom.read();
         PWMmoins = MessRecu - 48;
         nombre = nombre + PWMmoins;
         nombre = nombre * 10;
       }
    }
     nombre = nombre / 10;
}

void receptionPWM (){
  
   
       if (BlueCom.available()){
         MessRecu = BlueCom.read();
         Serial.write(MessRecu);
         PWMmoins = MessRecu - 48;
         valeurPWM = valeurPWM + PWMmoins;
         valeurPWM = valeurPWM * 10;
       }
    
     valeurPWM = valeurPWM / 10;
  
}


void setup() {                                            //void setup
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
}                                                           //fin void setup







void loop() {                                               // void loop
    
    
    tempsActu = millis();
    mot = 0;
    nombre = 0;
    led = 0;
    receptionMot();
    valeurPWM = 0; 

   
    
    if(mot == 1046){
      BlueCom.println("Chenillard");
      BlueCom.println();
      BlueCom.println();
       /* for(int n = 0; n<= 11 ; n++ ){                         //fait un chenillard
        digitalWrite(n, 1);
        delay(100);
        digitalWrite(n, 0);*/

        for(int n = 0; n <= 60 ; n++ ){                         //fait un chenillard
        analogWrite(9, n);
        delay(100);
      }
    }

    else if(mot == 1214){                                           // allume tout
      BlueCom.println("Toutes les lumieres sont allumer");
      BlueCom.println();
      BlueCom.println();
      for(int n = 0; n<= 11 ; n++ ){
        digitalWrite(n, 1);
      }
    }

    else if(mot == 1308){
      BlueCom.println("Toutes les lumieres sont eteinte");             // eteind tout 
      BlueCom.println();
      BlueCom.println();
      for(int n = 0; n<= 11 ; n++ ){
        digitalWrite(n, 0 );
      }
    }

    else if(mot == 754){
      BlueCom.println("Allumer quelle lumiere ?");                // demande quelle lumier allumer 
      receptionNombre();
      led=nombre - 48;
      BlueCom.print("Lumiere ");
      BlueCom.print(led);
      BlueCom.println(" allumer.");
      BlueCom.println();
      BlueCom.println();
      digitalWrite(led , 1);
    }

    else if(mot == 848){
      BlueCom.println("Eteindre quelle lumiere ?");                // demande quelle lumier eteindre
      receptionNombre();
      led=nombre - 48;
      BlueCom.print("Lumiere ");
      BlueCom.print(led);
      BlueCom.println(" eteinte.");
      BlueCom.println();
      BlueCom.println();
      digitalWrite(led , 0);
    }

    else if(mot == 340){
      BlueCom.println("Sur quelle sortie PWM effectuer la commande(9, 6, 5, 3 ) ?");                // sortie pwm
      receptionNombre();
      led=nombre - 48;
      BlueCom.println("Recu ");
      BlueCom.println("Quelle valeur PWM apliquer ? ");
      receptionPWM ();
      BlueCom.print("Comande effectuer sur la sortie ");
      BlueCom.print(led);
      BlueCom.println(" avec une valeur PWM etant");
      BlueCom.print("egale a  ");
      BlueCom.print(valeurPWM);
      BlueCom.println(" .");
      BlueCom.println();
      BlueCom.println();
      analogWrite(led, valeurPWM);
      
     
    }

    else{
      digitalWrite(11, 1);
      delay(100);
      digitalWrite(11, 0);
      delay(100);
    }



}                                                           // fin void loop


