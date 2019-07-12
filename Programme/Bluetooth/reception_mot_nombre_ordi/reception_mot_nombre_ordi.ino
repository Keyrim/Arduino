//pin 13 = txd
//pin 12 = rxd
#include <SoftwareSerial.h>
SoftwareSerial BlueCom(13, 12); 


char mot [250];
char messageRecu ;
byte i = 0;
String Mot ;
int nombre ;

void reception(){
  while(messageRecu != '\r'){
      
    
if(Serial.available()){
  
      messageRecu  = Serial.read();
      mot[i] = messageRecu ;
      i++ ;
    }
    
  }
 i -- ;
 mot[i] = 0 ;

 i = 0;
 Mot = mot ; 
 nombre = Mot.toInt();
 messageRecu = '}' ;
  
}

void setup() {
 BlueCom.begin(9600);
 Serial.begin(9600);
}

void loop() {
// sting : Mot
// int: nombre

reception();


if(Mot == "Allumer lumiere"){                           // pour allumer une lumiere precise 
  Serial.println("Allumer quelle lumiere ? ");
  reception();
  Serial.print("Lumiere  " );
  Serial.print(nombre);
  Serial.println(" allumer.");
  digitalWrite(nombre, HIGH);
     }                                                 //fin pour allumer une lumiere 

if(Mot == "Eteindre lumiere"){                           // pour eteindre une lumiere precise 
  Serial.println("Eteindre quelle lumiere ? ");
  reception();
  Serial.print("Lumiere    " );
  Serial.print(nombre);
  Serial.println(" eteinte.");
  digitalWrite(nombre, LOW);
     }                                                 //fin pour eteindre une lumiere 


}











