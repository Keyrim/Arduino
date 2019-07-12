


void setup() {
 pinMode(9 , OUTPUT);
 pinMode(10, OUTPUT);
 pinMode(11, OUTPUT);
 
}

void loop() {
  digitalWrite(9, 0);
  digitalWrite(10,0);
  digitalWrite(11,0);

  
  for(int n=0 ; n <= 254 ; n++){
    analogWrite(9, n);
    delay(10);
  }
  for(int x=0 ; x <= 254 ; x++){
    analogWrite(10, x);
    delay(10);
  }
  for(int z=0 ; z <= 254 ; z++){
    analogWrite(11, z);
    delay(10);
  }
 

}
