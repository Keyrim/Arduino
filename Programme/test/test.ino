#define pinLed 11
String Phrase;
char charactere[5] , phrase[200]; // 0
int nombre[5]; //0 1 2 



void lecteur ()
{
  if(Serial.available())
  { 
    charactere[0] = ' ' ;    nombre[0] = 0;
    while(charactere[0] != '\n')
    {
      if(Serial.available())
      {
        charactere[0] = Serial.read();
        phrase[nombre[0]] = charactere[0] ; nombre[0]++ ; 
      }      
    }
    phrase[nombre[0]] = 0 ; nombre[0] = 0; 
    Phrase = phrase ; 
    nombre[1] = Phrase.toInt();
  }
}

void pourcentage(int f){
  f = f * 10 ;
  digitalWrite(pinLed , HIGH);
  delayMicroseconds(f);
  digitalWrite(pinLed, LOW);
  delayMicroseconds(1000-f);
}
void reinitialisation ()
{
  for(int r = 0; r <201; r++){
    phrase[r] = ' ';
  }
  Phrase =phrase ;
}


void setup() {
 pinMode(pinLed, OUTPUT);    
 Serial.begin(9600);         
}

void loop() 
{ 
  lecteur();
  if(Phrase == "on\n" )digitalWrite(pinLed, HIGH);
  else if(Phrase == "off\n")digitalWrite(pinLed, LOW );  
  else
  {
    for(byte n = 0; n <= 200; n++)
    { int decalage (0);
      if(phrase[n] == '%')
      {
        if(phrase[n-3] <58 && phrase[n-3] > 47)decalage=3 ;
        else if (phrase[n-2] <58 && phrase[n-2] > 47)decalage = 2 ;
        else if (phrase[n-1] <58 && phrase[n-1] > 47)decalage = 1 ;
        phrase[decalage]= phrase[n] ;
        phrase[decalage -1]= phrase[n-1];
        phrase[decalage -2]= phrase[n-2];
        Phrase = phrase ;
        pourcentage(Phrase.toInt());
      }

    } 
  }
}















