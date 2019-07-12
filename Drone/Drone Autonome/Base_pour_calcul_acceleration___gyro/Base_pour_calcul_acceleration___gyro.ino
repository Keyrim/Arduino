//====== MPU-6050  ===========================================
// Demo mesure des valeurs brutes Acceleration - Gyro
// tiptopboards.com
// Modifié 30 08 2013
//
//=============================================================
// Source :  10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
//  https://github.com/jrowberg/i2cdevlib
//=============================================================
#include "Wire.h"  // Arduino Wire library
#include "I2Cdev.h"  //Installer ces 2 librairies
#include "MPU6050.h"
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

int16_t ax, ay, az;  //mesures brutes
int16_t gx, gy, gz;

int16_t ax_moy, ay_moy, az_moy;  //moyennes
int16_t gx_moy, gy_moy, gzv;

#define LED_PIN 13   //Clignotte pour indiquer le bon fonctionnement
bool blinkState = false;

void setup() {
    Wire.begin();  //I2C bus
    //Serial.begin(9600);  
     Serial.begin(38400);

    // initialize device
    Serial.println("Initialisation I2C...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Test de la conection du dispositif ...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection reussie" : "MPU6050 connection echec");
    pinMode(LED_PIN, OUTPUT);  //Allume la led
}

void loop() {
    // Lire les données brutes acceleration / gyro 
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    ax_moy = ax;
    // On peut aussi utiliser ces méthodes
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    // Affichage accel/gyro x/y/z 
    Serial.print("a/g:\t");
    Serial.print(ax); Serial.print("\t");
    Serial.print(ay); Serial.print("\t");
    Serial.print(az); Serial.print("\t");
    Serial.print(gx); Serial.print("\t");
    Serial.print(gy); Serial.print("\t");
    Serial.print(gz); Serial.print("\t");
    // x > 0 si bascule en avant (tanguage)
    // y > 0 si roulis du côté gauche
    // z > 0 si orienté en haut
    
    //== module détecteur de chocs ou d'accélérations (sans 1g)
    float module = (float)ax*ax + (float)ay*ay + (float)az*az;
    module = abs(sqrt(module)/1000-16);   //retirer 1g et absolu
    String etoiles = "*****************************";
    String nb_etoiles = etoiles.substring(0,(int)module);
    Serial.print(module);
    Serial.print(" ");
    Serial.println(nb_etoiles);  //module
    
    delay (100);
    blinkState = !blinkState;   //LED témoin d'activité clignotte
    digitalWrite(LED_PIN, blinkState);
}
