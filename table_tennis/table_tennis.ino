#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

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
const int payload_size = 32;
static char send_payload[payload_size];

RF24 radio(9, 10);

void setup() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(115200);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    //Serial.println("Testing device connections...");
    //Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    //set offsets
    
    accelgyro.setXAccelOffset(-6663);
    accelgyro.setYAccelOffset(1783);
    accelgyro.setZAccelOffset(1438);

    accelgyro.setXGyroOffset(26);
    accelgyro.setYGyroOffset(-17);
    accelgyro.setZGyroOffset(4);

    //sound sensor

    pinMode(SOUND_PIN, INPUT);

  //nrf
  radio.begin();
  radio.openWritingPipe(0xE8E8F0F0E1LL);
  radio.setChannel(0x77);
  radio.setPALevel(RF24_PA_MAX);
  radio.enableDynamicPayloads();
  radio.stopListening();
}

void loop() {
    accelgyro.getAcceleration(&ax, &ay, &az);

    soundLevel = analogRead(SOUND_PIN);

    str_ax = String(ax);
    str_ay = String(ay);
    str_az = String(az);
    str_soundLevel = String(soundLevel);

    string_buffer = str_ax + " " + str_ay + " " + str_az + " " + str_soundLevel;
    string_buffer.toCharArray(send_payload, payload_size);
    
    Serial.println(send_payload);

    radio.write(send_payload, payload_size);

}
