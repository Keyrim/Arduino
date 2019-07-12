#define entre1  2
#define entre2  3
#define entre3  4
#define entre4  5
#define entre5  6

#define sortie1  7
#define sortie2  8
#define sortie3  9
#define sortie4  10
#define sortie5  11

int signal1, signal2, signal3, signal4, signal5;
unsigned long timer;

void setup() {
 pinMode(entre1, INPUT);
 pinMode(entre2, INPUT);
 pinMode(entre3, INPUT);
 pinMode(entre4, INPUT);
 pinMode(entre5, INPUT);
 
 pinMode(entre1, OUTPUT);
 pinMode(entre2, OUTPUT);
 pinMode(entre3, OUTPUT);
 pinMode(entre4, OUTPUT);
 pinMode(entre5, OUTPUT);

}

void loop() {
  
  timer = millis();
  signal1 = pulseIn(entre1, HIGH, 2000);
  signal2 = pulseIn(entre2, HIGH, 2000);
  signal3 = pulseIn(entre3, HIGH, 2000);
  signal4 = pulseIn(entre4, HIGH, 2000);
  signal5 = pulseIn(entre5, HIGH, 2000);
  timer = millis() - timer ;
  Serial.println(timer);
  d
  delay(100);
  

}









