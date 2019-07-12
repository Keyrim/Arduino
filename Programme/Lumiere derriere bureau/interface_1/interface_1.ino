//11 rouge 10 vert 9 bleuà
#define bleu 9
#define vert 10
#define rouge 11
#define ground 12

void setup() {
  pinMode(bleu, OUTPUT);
  pinMode(vert, OUTPUT);
  pinMode(rouge, OUTPUT);
  pinMode(ground, OUTPUT);
  digitalWrite(ground, HIGH);
  digitalWrite(bleu, HIGH);
  digitalWrite(rouge, HIGH);
  digitalWrite(vert, HIGH);
}

void loop() {
  bool montantDescandant = 0;
  int temps = 10, intensiteMax = 0 ;


  for(int n = 255 ; n >= intensiteMax; n--)
  {
    analogWrite(rouge, n);
    delay(temps);
  }
  for(int n = intensiteMax ; n <256; n++)
  {
    analogWrite(vert, n);
    delay(temps);
  }
  for(int n = 255 ; n >= intensiteMax; n--)
  {
    analogWrite(bleu, n);
    delay(temps);
  }
  for(int n = intensiteMax ; n <256; n++)
  {
    analogWrite(rouge, n);
    delay(temps);
  }
  for(int n = 255 ; n >= intensiteMax; n--)
  {
    analogWrite(vert, n);
    delay(temps);
  }
  for(int n = intensiteMax ; n <256; n++)
  {
    analogWrite(bleu, n);
    delay(temps);
  }

}








