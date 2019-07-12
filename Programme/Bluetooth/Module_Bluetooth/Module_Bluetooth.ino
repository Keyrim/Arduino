//pin 13 = txd
//pin 12 = rxd



#include <SoftwareSerial.h>

SoftwareSerial BlueCom(13, 12);
 
int MessRecu;
int led;
int tempsActu;

void setup() {
  for(int n = 0; n <=11; n++){
    pinMode(n, OUTPUT);
  }

 BlueCom.begin(9600);
 Serial.begin(9600);

  BlueCom.println("bonjour");
  BlueCom.println("je suis pret");
}

void loop() {

   

   if (BlueCom.available())
   {

     MessRecu = BlueCom.read();
     Serial.print(MessRecu);
     Serial.println();

    

     led = MessRecu-46 ;
      
     if(led ==  02){
      BlueCom.println("Toutes les lumiéres sont eteinte.");
      for(int n = 0; n <=11; n++){
      digitalWrite(n, LOW);
  }

     }

     if(led <= 13 && led > 2){
      digitalWrite(led , 1);
      BlueCom.print("lumiere ");
      BlueCom.print(led );
      BlueCom.println(" allume. ");
     }
     
   }
   

}


