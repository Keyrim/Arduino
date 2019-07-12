



#define trigPin 13  //Trig Ultrasons (sortie)
#define echoPin 12  //Echo Ultrasons (entrée)



void setup() {

  Serial.begin(9600);
  
  Serial.begin (9600);  
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée

 pinMode(9 , OUTPUT);
 pinMode(10, OUTPUT);
 pinMode(11, OUTPUT);

}

void loop() {

  
  long duration, distance;
  
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Trig déclenché 10ms sur HIGH
  digitalWrite(trigPin, LOW);
  
  // Calcul de l'écho
  duration = pulseIn(echoPin, HIGH);
  // Distance proportionnelle à la durée de sortie
  distance = duration*340/(2*10000);  //Vitesse du son théorique



   

  if(distance <= 300 && distance > 0){             // si je capte
    
    int n = map(distance ,0 ,300 ,255 ,0); 
   
    analogWrite(9, n);
    analogWrite(10, n);
    analogWrite(11, n); 
    Serial.print(distance) ;
   Serial.print("       ") ;
   Serial.println(n) ;
   delay(200); 

  }
 
   

}

