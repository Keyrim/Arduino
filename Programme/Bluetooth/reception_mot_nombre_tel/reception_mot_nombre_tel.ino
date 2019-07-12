//pin 13 = txd
//pin 12 = rxd
#include <SoftwareSerial.h>
SoftwareSerial BlueCom(13, 12);

/*void reception(){
  if(bluecom.available()){
   while(messRecu != '/r'
  }
}*/

void setup() {
 BlueCom.begin(9600);
 Serial.begin(9600);

}

void loop() {
// sting : Mot
// int: nombre
if(BlueCom.available()){
  char mess = BlueCom.read() ;
  if(mess == '2')BlueCom.println("lol");
  Serial.print(mess);
}



}











