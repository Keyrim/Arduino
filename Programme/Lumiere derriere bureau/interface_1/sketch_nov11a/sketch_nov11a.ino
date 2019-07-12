


#define trigPin 13  //Trig Ultrasons (sortie)
#define echoPin 12  //Echo Ultrasons (entrée)

long duration, distance;
char mot [250];
char messageRecu ;
byte i = 0;
String Mot ;
int nombre, tailleTableau ;

void reception(){
      while(messageRecu != '\r'){   
    if(Serial.available()){   
       messageRecu  = Serial.read();
       mot[i] = messageRecu ;
       i++ ;
      }
    }
  i -- ;
  mot[i] = 0 ;
  tailleTableau = i ;

  i = 0;
  Mot = mot ; 
  nombre = Mot.toInt();
  messageRecu = '}' ;
  digitalWrite(10, HIGH);
  

}
int fonction(String couleur)
{
  if(couleur == "rouge"){
    digitalWrite(11, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    return 2 ;
  }
  else if(couleur == "bleu"){
    digitalWrite(11, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);   
    return 3 ; 
  }
  else if(couleur == "vert"){
    digitalWrite(11, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(8, HIGH);
    return 4 ;    
  }
  else if(couleur == "violet"){
    digitalWrite(11, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW); 
    return 5 ;
  }
  else if(Mot == "rien"){
    digitalWrite(11, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    return 6 ;
  }
  else if(Mot == "tout"){
    digitalWrite(11, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW); 
    return 7 ;
  }
  
  else return 0;
}
int calculDistance(){
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Trig déclenché 10ms sur HIGH
  digitalWrite(trigPin, LOW);

  // Calcul de l'écho
  duration = pulseIn(echoPin, HIGH);
  // Distance proportionnelle à la durée de sortie
  distance = duration*340/(2*10000);  //Vitesse du son théorique
  return distance ;

}

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
  pinMode(11, OUTPUT);digitalWrite(11, HIGH);
  pinMode(10, OUTPUT);digitalWrite(10, HIGH);
  pinMode(9, OUTPUT);digitalWrite(9, HIGH);
  pinMode(8, OUTPUT);digitalWrite(8, HIGH);
  pinMode(7, OUTPUT);digitalWrite(7, HIGH);

  
}

void loop() {
  if(Serial.available()){
    reception();
    if(Mot == "couleur"){
      reception();
      fonction(Mot);
    }
    else if(Mot == "high"){
      digitalWrite(7, HIGH);
    }
    else if(Mot =="low"){
      digitalWrite(7, LOW);
    }
    else if(Mot == "close"){
      digitalWrite(11, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
    }
  }
  delay(100);
}











