
#define trigPin 13  //Trig Ultrasons (sortie)
#define echoPin 12  //Echo Ultrasons (entrée)

float angleX(37), tanX, angleY(43), tanY ;
float distanceAuSol , distanceUltrasson(50);
int temps;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
  temps = millis();
  Serial.println(micros());
  
}

void loop() {

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
  //distanceUltrasson = pulseIn(echoPin, LOW)/ (float)58.82 ;
  tanX = tan(angleX);
  tanY = tan(angleY);
  distanceAuSol = pow(tanX, 2) + pow(tanY, 2) + 1 ;
  distanceAuSol = pow(distanceUltrasson, 2) / distanceAuSol ;
  distanceAuSol = sqrt(distanceAuSol);
  Serial.println(micros());
  delay(10);
  Serial.println(distanceAuSol);  
  while(1);
   
    
  
  
}
