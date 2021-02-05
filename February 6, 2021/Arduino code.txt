#include <SPI.h>
#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 accelgyro;
int16_t ax, ay, az;

int soundLevel;

String str_ax, str_ay, str_az, str_soundLevel, string_buffer;

#define OUTPUT_READABLE_ACCELGYRO

#define SOUND_PIN A2

void setup() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(115200);

    // initialize device
    accelgyro.initialize();

    //set offsets
    
    accelgyro.setXAccelOffset(-6663);
    accelgyro.setYAccelOffset(1783);
    accelgyro.setZAccelOffset(1438);

    accelgyro.setXGyroOffset(26);
    accelgyro.setYGyroOffset(-17);
    accelgyro.setZGyroOffset(4);

    //sound sensor

    pinMode(SOUND_PIN, INPUT);

}

void loop() {
    accelgyro.getAcceleration(&ax, &ay, &az);

    soundLevel = analogRead(SOUND_PIN);

    str_ax = String(ax);
    str_ay = String(ay);
    str_az = String(az);
    str_soundLevel = String(soundLevel);

    string_buffer = str_ax + " " + str_ay + " " + str_az + " " + str_soundLevel;
    
    Serial.println(string_buffer);

}