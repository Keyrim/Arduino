//pin 13 = txd
//pin 12 = rxd
#include <SoftwareSerial.h>
SoftwareSerial BlueCom(13, 12); 


char mot [250];
char messageRecu ;
byte i = 0;
String Mot ;
int nombre ;

void setup() {
 BlueCom.begin(9600);
 Serial.begin(9600);
}

void receptionMot(){
    messageRecu  = BlueCom.read();
      if(messageRecu != '#' ){
         mot[i] = messageRecu ;
         i++ ;
      }
      else{
        mot[i] = 0 ;
        i = 0;
        Mot = mot ;
        nombre = Mot.toInt();
        
      }
  
}

void loop() {

if(BlueCom.available()){
  
  messageRecu  = BlueCom.read();
  
  if(messageRecu == '#'){
    mot[i] = 0 ;
    i = 0;
    Mot = mot ;
    nombre = Mot.toInt();
    Serial.println(nombre);
    if(nombre == 321){
      Serial.println ("Zerooooooooooo " );
    }
    
  }
    
     
    else{
      mot[i] = messageRecu ;
    i++ ;
    }
}
 
  
  
    
 
  


}












