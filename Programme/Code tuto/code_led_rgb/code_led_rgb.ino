


int ledRougePin = 9; // PWM
int ledVertPin = 10; // PWM
int ledBleuPin = 11; // PWM

void setup(){
  pinMode( ledRougePin, OUTPUT );
  pinMode( ledVertPin, OUTPUT );
  pinMode( ledBleuPin, OUTPUT );
  
  
 
    
    

/*
  Active une couleur à la fois.
  Vous pouvez modifier le code pour allumer plusieurs couleurs
    en meme temps.
 */
void couleursSimple(){
  // allumer Vert
  digitalWrite( ledRougePin, HIGH ); 
  digitalWrite( ledVertPin, LOW ); 
  digitalWrite( ledBleuPin, HIGH ); 
  // Attendre 1 sec
  delay( 100 );
  // allumer Rouge
  digitalWrite( ledRougePin, LOW ); 
  digitalWrite( ledVertPin, HIGH ); 
  digitalWrite( ledBleuPin, HIGH ); 
  // Attendre 1 sec
  delay( 100 );
  // allumer Bleu
  digitalWrite( ledRougePin, HIGH ); 
  digitalWrite( ledVertPin, HIGH ); 
  digitalWrite( ledBleuPin, LOW ); 
  // Attendre 1 sec
  delay( 100 );
}

/* 
   Cette fonction passe d'une couleur à l'autre en fondue
   enchainé dans l'ordre suivant:
     Rouge -> Vert --> Bleu --> Rouge --> Vert --> ...
 */
void couleursFondue(){
  // allumer Rouge
  digitalWrite( ledRougePin, LOW ); 
  digitalWrite( ledVertPin, HIGH ); 
  digitalWrite( ledBleuPin, HIGH ); 
  // Ajouter progressivement du vert
  // Retirer progressivement du rouge
  //   attention: 255 = pas de couleur, 0 = max de couleur
  for( int iVert = 255; iVert>0; iVert-- ) {
    int iRouge = 255 - iVert;
    analogWrite( ledRougePin, iRouge );
    analogWrite( ledVertPin, iVert );
    delay( 20 );
  }
  // Ajouter progressivement du bleu
  // Retirer progressivement du vert
  //   attention: 255 = pas de couleur, 0 = max de couleur
  for( int iBleu = 255; iBleu>0; iBleu-- ) {
    int iVert = 255 - iBleu;
    analogWrite( ledVertPin, iVert );
    analogWrite( ledBleuPin, iBleu );
    delay( 20 );
  }
  // Ajouter progressivement du rouge
  // Retirer progressivement du bleu
  //   attention: 255 = pas de couleur, 0 = max de couleur
  for( int iRouge = 255; iRouge>0; iRouge-- ) {
    int iBleu = 255 - iRouge;
    analogWrite( ledBleuPin, iBleu );
    analogWrite( ledRougePin, iRouge );
    delay( 20 );
  }
}

void loop(){
   couleursFondue();
}
 
   
