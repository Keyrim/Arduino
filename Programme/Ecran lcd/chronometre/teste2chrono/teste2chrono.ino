// include the library code:
#include <LiquidCrystal.h>

#define trigPin 13  //Trig Ultrasons (sortie)
#define echoPin 12  //Echo Ultrasons (entrée)




// Lcd + pinout
LiquidCrystal lcd(10, 11, 5, 4, 3, 2);

//Variable
#define  AnalogBtnPin A0
int n = 0;
int a = 0;

long TempsInit = 0;
long TempsReel = 0;
long TempsSec = 0;
long TempsMil = 0;
long TempsMin = 0;
long TempsHeu = 0 ;

long T1 = 0;
long T2 = 0;
long duration, distance = 0;

void setup() {

  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  lcd.begin(16, 2);



} // fin setup



void loop() {


  digitalWrite(trigPin, LOW);                                         // calcule distance
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Trig déclenché 10ms sur HIGH
  digitalWrite(trigPin, LOW);

  // Calcul de l'écho
  duration = pulseIn(echoPin, HIGH);
  // Distance proportionnelle à la durée de sortie
  distance = duration * 340 / (2 * 10000); //Vitesse du son théorique     // calcule distance



  if  (distance > 0 && distance <= 20)// si je capte
  {
               for(int f = 0; f == 0; f++){
                delay (100);
               }
                
                
               


    TempsInit = (millis());

    while (1) {
      
       





      digitalWrite(trigPin, LOW);                                         // calcule distance
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); //Trig déclenché 10ms sur HIGH
      digitalWrite(trigPin, LOW);

      // Calcul de l'écho
      duration = pulseIn(echoPin, HIGH);
      // Distance proportionnelle à la durée de sortie
      distance = duration * 340 / (2 * 10000); //Vitesse du son théorique     // calcule distance



      if (distance > 5 && distance < 50) {




        lcd.setCursor(4, 0);
        lcd.print( TempsHeu );
        lcd.setCursor(8, 0);
        lcd.print( TempsMin );
        lcd.setCursor(11, 0);
        lcd.print( TempsSec ) ;
        lcd.setCursor(14, 0);
        lcd.print( TempsMil );
        

       
         T1 = TempsSec + 5;
         digitalWrite(6, HIGH);


      }
      if (T1  < TempsSec) {
         digitalWrite(6,LOW);
         T1 = 60;
          }
    
      


      TempsReel = (millis() - TempsInit);
      TempsSec = ((TempsReel / 1000) % 60) ;
      TempsMil = (TempsReel % 1000) / 10;
      TempsMin = (TempsReel / 1000) / 60;
      TempsHeu = (TempsReel / 1000) / 3600;





      //Affichage + de 10
      if (TempsHeu >= 10 ) {
        lcd.setCursor(6, 1);
        lcd.print(TempsHeu, DEC);
      }



      if (TempsMin >= 10 ) {
        lcd.setCursor(9, 1);
        lcd.print(TempsMin, DEC);
      }


      if (TempsSec >= 10 ) {
        lcd.setCursor(11, 1);
        lcd.print(TempsSec, DEC);
      }

      if (TempsMil >= 10 ) {
        lcd.setCursor(14, 1);
        lcd.print(TempsMil, DEC);
      }

      //Affichage - de 10
      if (TempsHeu < 10 ) {
        lcd.setCursor(6, 1);
        lcd.print(" ");
        lcd.setCursor(5, 1);
        lcd.print(TempsHeu, DEC);
      }

      if (TempsMin < 10 ) {
        lcd.setCursor(8, 1);
        lcd.print(" ");
        lcd.setCursor(9, 1);
        lcd.print(TempsMin, DEC);
      }

      if (TempsSec < 10 ) {
        lcd.setCursor(11, 1);
        lcd.print(" ");
        lcd.setCursor(12, 1);
        lcd.print(TempsSec, DEC);
      }


      if (TempsMil < 10 ) {
        lcd.setCursor(14, 1);
        lcd.print(" ");
        lcd.setCursor(15, 1);
        lcd.print(TempsMil, DEC);
      }




      
      while(distance < 10 && distance > 0){
        
          digitalWrite(trigPin, LOW);                                         // calcule distance
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); //Trig déclenché 10ms sur HIGH
      digitalWrite(trigPin, LOW);

      // Calcul de l'écho
      duration = pulseIn(echoPin, HIGH);
      // Distance proportionnelle à la durée de sortie
      distance = duration * 340 / (2 * 10000); //Vitesse du son théorique     // calcule distance

      delay(1000);
      T2 ++;
      Serial.println(T2);
      }



      Serial.println(T2);
    

      


    } // While



  } // if distance

}//fin loop

