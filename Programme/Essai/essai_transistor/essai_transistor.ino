// Define which pin to be used to communicate with Base pin of TIP120 transistor
 int TIP120pin = 11; //for this project, I pick Arduino's PMW pin 11
 int n;
 
 void setup()
 {
  Serial.begin(9600);
 pinMode(TIP120pin, OUTPUT); // Set pin for output to control TIP120 Base pin
  
 }

 void loop()
 {
  n = analogRead(0);
  n = map(n, 0, 1023, 0, 255);
  analogWrite(TIP120pin, n);
  Serial.println(n);
 }

