//Conection :
//MPU Sda : A4
//MPU Scl : A5
//PPM input : D2
//Motor 1 PWM : D9
//Motor 2 PWM : D10
//Motor 3 PWM : D11
//Motor 4 PWM : D12


#include <Wire.h>
#include <Servo.h>
const int MPU=0x68;  // I2C address of the MPU-6050

//Read PPM signal
const byte number_of_chanel = 11 ;
byte actual_chanel = 0 ;
unsigned long previous_timer_rising = 0 ;
unsigned int  chanels[number_of_chanel] ;

//Constante compensation (PID coefs)
const float kp_roll = 1.0, kp_pitch = 1.0, kp_yaw = 1.0 ;
const float kd_roll = 0.0, kd_pitch = 0.0 ;
const float ki_roll = 0.0, ki_pitch = 0.0 ;
int compensation_max = 200;

//Error variables
float roll_error, pitch_error ;
float roll_previous_error = 0, pitch_previous_error=0;

//Rc orders 
const int inclination_max = 45 ; //(degrees)
const int max_roration_rate = 100 ; //(degrees per second for the yax axis control)
float roll_order = 0, pitch_order = 0, yaw_order ;



//Check for the compensation and motor orders
float check_compensation(float comp)
{
  if(comp < -compensation_max)return -compensation_max ;
  else if(comp > compensation_max)return compensation_max ;
  else return comp ;
}
int check_motor_order(int order)
{
  if(order < 1000)return 1000 ;
  else if(order > 2000)return 2000 ;
  else return order ;
}



//Motor Instanciation
Servo moteur1 ;
Servo moteur2 ;
Servo moteur3 ;
Servo moteur4 ;
unsigned int global_power = 1000;


//timer things
unsigned long loop_timer ; 
unsigned long start_timer_esc ;
const int frequence = 250; //Frequence of the loop in hz
//raw data
float AcX, AcY, AcZ, GyX=0, GyY=0, GyZ=0;
float X=0, Y=0;

void read_mpu()
{
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);       //Send the starting register (accelerometer)
    Wire.endTransmission();
    Wire.requestFrom(MPU, 6);
    while (Wire.available()< 6);
    AcX = Wire.read()<<8|Wire.read();
    AcY = Wire.read()<<8|Wire.read();
    AcZ = Wire.read()<<8|Wire.read();

    //Get the true raws values in g according to our setting
    AcZ /= 8192;
    AcX /= 8192;
    AcY /= 8192;
    
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission();
    Wire.requestFrom(MPU, 6);

    while(Wire.available()< 6);
    GyX = (Wire.read()<<8|Wire.read())/65.5;
    GyY = (Wire.read()<<8|Wire.read())/65.5;  
    GyZ = (Wire.read()<<8|Wire.read())/65.5;  

}



void setup()
{
  //Motor assignement
  moteur1.attach(9);
  moteur2.attach(10);
  moteur3.attach(11);
  moteur4.attach(12);
  
  // Wake up the mpu 
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();

  //Set up the accelerometer
  //1g = 8192
  //+- 4g
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0x08);
  Wire.endTransmission();

  //Set up the gyroscope
  //1deg/s = 65.5 
  //+- 500
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0X08);
  Wire.endTransmission();
  
  //      PPM signal setup
  attachInterrupt(digitalPinToInterrupt(2), rising, RISING);

  //Serial part
  Serial.begin(115200);

  //Start the timer for the PPM Signal
  previous_timer_rising = micros();
}

void loop()
{
  read_mpu();
  //Compute our raw values
  float total_vector = sqrt(AcX*AcX + AcY*AcY + AcZ*AcZ);    
  AcX = asin(AcX/total_vector)*57.32; //arcsin c'est en radian 
  AcY = asin(AcY/total_vector)*57.32;
  
  //Complementary filter
  X += GyX / frequence ; 
  X = X * 0.996 + AcY * 0.004 ;
  Y += GyY / frequence ;
  Y = Y * 0.996 + ACX * 0.004;

  //Rc setpoint calculation
  global_power = chanels[3];
  roll_order = map(chanels[1], 1000, 2000, -inclination_max, inclination_max);
  pitch_order = map(chanels[2], 1000, 2000, -inclination_max, inclination_max);
  yaw_order = map(chanels[3], 1000, 2000, -max_rotation_rate, max_rotation_rate);

  
  
  
  moteur1.writeMicroseconds(global_power);
  moteur2.writeMicroseconds(global_power);
  moteur3.writeMicroseconds(global_power);
  moteur4.writeMicroseconds(global_power);
  Serial.println(micros()-loop_timer);
  
  //We regulate our frequence here
  while(micros()<loop_timer + 1000000/frequence);
  loop_timer = micros();
  
}

void rising()
{
  unsigned int signal_ppm = micros()-previous_timer_rising ;
  if (signal_ppm > 3000) 
  {
    actual_chanel = 0 ;
    previous_timer_rising = micros();
    chanels[actual_chanel] = signal_ppm ;
  }
  

  else 
  {
    actual_chanel ++;
    if (actual_chanel == number_of_chanel) actual_chanel = 0 ;
    chanels[actual_chanel] = signal_ppm ;
    previous_timer_rising = micros();
  }
  

  
  
}
