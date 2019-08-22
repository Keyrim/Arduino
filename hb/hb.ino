#define pin_stepper_steps 26
#define pin_stepper_sens 27

//Global music things
float do3 = 32.703;
int bpm = 70;
float rapport = 1.05946 ;
float bpm_period = (60000/bpm)  ; //(time 1000 cuz we use millis())
int note_number  = 0 ;

//Loop period for the bpm
unsigned long last_time_bpm ;
unsigned long last_time_note ;

//happy happy_birthday things
int happy_birthday_note[] =  {2, 2, 3, 2, 7, 6, 2, 2, 3, 2, 9, 7, 2, 2, 14, 11, 7, 6, 4, 12, 12, 11,7, 9, 7};
float happy_birthday_note_duration[] = {0.5, 0.5, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 1, 2};
int happy_birthday_length = 25 ;


void setup ()
{
    pinMode(pin_stepper_sens, OUTPUT);
    pinMode(pin_stepper_steps, OUTPUT);
    digitalWrite(pin_stepper_sens, LOW);
    digitalWrite(pin_stepper_steps, LOW);
    last_time_bpm = millis();
    Serial.begin(115200);
    last_time_note = micros();
}

void loop ()
{

    if(millis() > last_time_bpm + bpm_period * happy_birthday_note_duration[note_number])
    {
        note_number ++ ;
        if (note_number == 25) note_number = 0 ;       
        last_time_bpm = millis(); 
        delay(200);
    }
    //Serial.println(do3 * pow(rapport, happy_birthday_note[note_number]));
    if(micros() > last_time_note + (1000000/(do3 * pow(rapport, happy_birthday_note[note_number]) )))
    {
        digitalWrite(pin_stepper_steps, HIGH);
        digitalWrite(pin_stepper_steps, LOW);
        last_time_note = micros();
    }
}