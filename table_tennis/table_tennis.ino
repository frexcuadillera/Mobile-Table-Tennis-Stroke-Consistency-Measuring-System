#include <SPI.h>
//#include <nRF24L01.h>
//#include <RF24.h>

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

//nrf variables
//const int payload_size = 32;
//static char send_payload[payload_size];
//
//RF24 radio(9, 10);

void setup() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(115200);

    // initialize device
    //Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    //Serial.println("Testing device connections...");
    //Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    //set offsets
    
    accelgyro.setXAccelOffset(-1744);
    accelgyro.setYAccelOffset(-1645);
    accelgyro.setZAccelOffset(4760);

    accelgyro.setXGyroOffset(79);
    accelgyro.setYGyroOffset(-157);
    accelgyro.setZGyroOffset(101);

    //sound sensor

    pinMode(SOUND_PIN, INPUT);

  //nrf
//  radio.begin();
//  radio.setPALevel(RF24_PA_MAX);
//  radio.setChannel(0x76);
//  radio.openWritingPipe(0xF0F0F0F0E1LL);
//  radio.setDataRate(RF24_1MBPS);
//  radio.enableDynamicPayloads();
//  radio.powerUp();
//  radio.stopListening();
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
