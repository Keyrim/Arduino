/*
  Mesure de la température à l'aide d'un TMP36
  Affichage sur LCD: MOP-AL162A-BBTW: LCD 2x16
 
 Le montage:
 Afficheur LCD
 * LCD RS     - pin 12
 * LCD Enable - pin 11
 * LCD D4     - pin 5
 * LCD D5     - pin 4
 * LCD D6     - pin 3
 * LCD D7     - pin 2
 * LCD R/W    - GND
 * LCD Vo contrast- potentiomètre 10K (entre Gnd et +5V)
 
 Senseur de température:
 * TMP36 Analog Output - Pin A0 (analogique)
 
 This example code is in the public domain.
 
*/

// include the library code:
#include <LiquidCrystal.h>


int tempSensorPin = 0; // Pin analogique pour lecture de la tension de sortie du TMP36 (Vout).
                       // Resolution: 10 mV / degree celsius avec une offset de 500 mv.

// Definition du caractere °
byte degrees[8] = {
  B00000,
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
};

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(10, 11, 5, 4, 3, 2);

void setup(){
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600);
  
  // initialiser le caractère ° dans le LCD
  lcd.createChar( 0, degrees );
}

// mémorise la dernière température affichée
int lastTemp = -100;

void loop(){
  float temp = lectureTemp();
  
  // rafraichit le LCD que si la 
  // température a varié sensiblement
  if( abs(temp-lastTemp)<0.20 )
    return;
  lastTemp = temp;
  
  // Afficher la valeur en evitant le
  //   lcd.clear(), pour éviter l'effet de
  //   scintillement.
  lcd.setCursor(0,0);
  lcd.print( temp - 4 );
                                                       // lcd.write( 0 );  // affiche le signe degré 
  lcd.print( "c" );

  Serial.print(temp - 4 );
  Serial.println("c");

  // Efface les derniers caractères si
  //   la température chute subitement
  lcd.print( "      " );
  
  // ne pas rafraichir trop souvent
  delay(800);
  
}

//Description:
//  Lecture de la température sur la pin A0
//
//Returns:
//  La température en degré Celcius.
//
float lectureTemp(){
 // Lecture de la valeur sur l'entrée analogique
 // Retourne une valeur entre 0->1024 pour 0->5v
 int valeur = analogRead(tempSensorPin);  

 // Converti la lecture en tension
 float tension = valeur * 5.0;
 tension /= 1024.0; 
 
 // Convertir la tension (mv) en temperature
 float temperature = ((tension * 1000) - 500) / 10;
 
 return temperature;
}

