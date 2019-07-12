
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
    Wire.begin();
    Serial.begin(57600);
    accelgyro.initialize();
}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    ax = map(ax, -32767, 32767, -255, 255);
    ay = map(ay, -32767, 32767, -255, 255);
    az = map(az, -32767, 32767, -255, 255);

    Serial.print(ax); Serial.print("\t");
    Serial.print(ay); Serial.print("\t");
    Serial.print(ay); Serial.print("\t");
    Serial.print(az); Serial.print("\t");
    Serial.print(gx); Serial.print("\t");
    Serial.print(gy); Serial.print("\t");
    Serial.print(gz); Serial.print("\t\n");
    
    delay(50);
}
