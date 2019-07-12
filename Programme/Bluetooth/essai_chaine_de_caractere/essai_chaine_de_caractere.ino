//pin 13 = txd
//pin 12 = rxd
#include <SoftwareSerial.h>
SoftwareSerial BlueCom(13, 12); 


char mot [250];
char messageRecu ;
byte i = 0;
String Mot ;

void setup() {
 BlueCom.begin(9600);
 Serial.begin(9600);
}

void loop() {

if(BlueCom.available()){
  messageRecu  = BlueCom.read();
  
  
  if(messageRecu == '#'){
    mot[i] = 0 ;
    i = 0;
    Mot = mot ;
       if(Mot == "bonjour" ){
          BlueCom.println("Bienvenue");
          }
       else{
          BlueCom.println("Je n'ai pas compris");
          }
    }
     
    else{
      mot[i] = messageRecu ;
    i++ ;
    }
    
 
  }


}













