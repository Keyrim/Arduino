//pin 13 = txd
//pin 12 = rxd
#include <SoftwareSerial.h>
SoftwareSerial BlueCom(13, 12);
#define trigPin 11  //Trig Ultrasons (sortie)
#define echoPin 10  //Echo Ultrasons (entrée)
 

long duration, distance;
char mot [250];
char messageRecu ;
byte i = 0;
String Mot ;
int nombre ;

void calculDistance(){
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Trig déclenché 10ms sur HIGH
  digitalWrite(trigPin, LOW);

  // Calcul de l'écho
  duration = pulseIn(echoPin, HIGH);
  // Distance proportionnelle à la durée de sortie
  distance = duration*340/(2*10000);  //Vitesse du son théorique

}

void receptionLoop(){
  if(BlueCom.available()){
    
  while(messageRecu != '#'){
      
    
if(BlueCom.available()){
  
      messageRecu  = BlueCom.read();

      if(messageRecu != '#'){
      BlueCom.print(messageRecu);
      mot[i] = messageRecu ;
      i++ ;
      }
    }
    
  }

  

 mot[i] = 0 ;

 i = 0;
 Mot = mot ; 
 nombre = Mot.toInt();
 messageRecu = '}' ;
 BlueCom.println();
  
}
}

void reception(){
  
    
  while(messageRecu != '#'){
      
    
if(BlueCom.available()){
  
      messageRecu  = BlueCom.read();
     if(messageRecu != '#'){
      mot[i] = messageRecu ;
      i++ ;
      BlueCom.print(messageRecu);
      }
    }
    
  }
 mot[i] = 0 ;
 BlueCom.println();
 i = 0;
 Mot = mot ; 
 nombre = Mot.toInt();
 messageRecu = '}' ;
  
}


void setup() {
 BlueCom.begin(9600);
 Serial.begin(9600);
 BlueCom.println();
 BlueCom.println("Bonjour, je suis pret");
 BlueCom.println();
 for(int l = 0; l<= 11; l++){
  pinMode(l, OUTPUT);
 }
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
}

void loop() {
// sting : Mot
// int: nombre

receptionLoop();

if(Mot == "?"){
  BlueCom.println("Toutes les comande que je comprend sont :");
  BlueCom.println("Allumer lumiere = Al");
  BlueCom.println("Eteindre lumiere = El");
  BlueCom.println("Tout eteindre = Te");
  BlueCom.println("Tout alumer = Ta");
  BlueCom.println("Regler la tension de sortie une sortie PWM = Pwm");
  BlueCom.println("Calculer la distance de maniere continue(fonction distance) = Fd");
  BlueCom.println("Pour areter une fonction quelconque = fin");
}


if(Mot == "Al"){                           // pour allumer une lumiere precise 
  BlueCom.println("Allumer quelle lumiere ? ");
  reception();
  BlueCom.print("Lumiere  " );
  BlueCom.print(nombre);
  BlueCom.println(" allumer.");
  digitalWrite(nombre, HIGH);
     }                                                 //fin pour allumer une lumiere 

if(Mot == "El"){                           // pour eteindre une lumiere precise 
  BlueCom.println("Eteindre quelle lumiere ? ");
  reception();
  BlueCom.print("Lumiere    " );
  BlueCom.print(nombre);
  BlueCom.println(" eteinte.");
  digitalWrite(nombre, LOW);
     }                                                   //fin pour eteindre une lumiere 


if(Mot == "Te"){
  BlueCom.println("Toutes les liumieres sont eteintes");
  for(int o = 0; o <= 11; o++){
    digitalWrite(o, 0);
  }
}

if(Mot == "Ta"){
  BlueCom.println("Toutes les lumieres sont allumer");
  for(int o = 0; o <= 11; o++){
    digitalWrite(o, 1);
  }
}
if(Mot == "Pwm"){
  BlueCom.println("Sur quelle sortie voulez-vous effectuez la comande ?");
  reception();
  int led = nombre ;
  BlueCom.println("Quelle valeur souhaitez-vous apliquer a la sorti ?");
  reception();
  BlueCom.print("Comande effectuez sur la sortie ");
  BlueCom.print(led);
  BlueCom.print(" avc une valeur de ");
  BlueCom.println(nombre);
  analogWrite(led, nombre);
}

if(Mot == "Fd"){
 while(Mot != "fin"){
  calculDistance();
   if(distance < 310){
  BlueCom.print("La distance est de : ");
  BlueCom.print(distance);
  BlueCom.println(" centimetre.");
  receptionLoop();
   }
  else{
    BlueCom.println("Hors de porter");
   }
  delay(100);
   
 }
  BlueCom.println("Fin de la fonction.");
}


if(BlueCom.available()){
Serial.println(Mot);
}
Mot = "aaaaaa" ;
}











