int joysticx ;      //HAUT   BAS
int joysticy ;      //DROITE GAUCHE 
int k ;

long x  ;
long y  ;
long xy ;


void setup() {
  Serial.begin(115200);

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {

  joysticx = analogRead(A0);
  x = map(joysticx, 0, 1023,5, 15);
  Serial.print(x);
  Serial.print("        ");

  joysticy = analogRead(A1);
  y = map(joysticy, 0, 1023,1, 11);
  Serial.print(y);
  Serial.print("        ");

  xy = x * y ;

  Serial.println(xy);

  k = map(xy ,5 ,150  ,4 ,12);

  delay(100);
  

   digitalWrite(k, 1);
   delay(10);
   digitalWrite(k, 0);
 

}
