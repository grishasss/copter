#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <FS.h>
#include <WiFiUdp.h>




#define R1 1000
#define R2 1000


Adafruit_MPU6050 mpu;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

float get_voltage(){
    return (analogRead(A0)) / 1024 * (R1 + R2) / R2;    
}






void setup() {
   Serial.begin(115200);
   bool is_mpu_begin = mpu.begin();
   bool is_mag_begin = mag.begin();
}

void loop() {
  
}
