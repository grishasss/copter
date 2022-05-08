#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "Adafruit_VL53L0X.h"

#include <FS.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>



#define R1 1000
#define R2 1000


ESP8266WebServer server(80);


Adafruit_MPU6050 mpu;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();




float get_voltage(){
    return (analogRead(A0)) / 1024 * (R1 + R2) / R2;    
}







void setup() {
    Serial.begin(115200);
    WiFi.softAP("efs", "12345678");
    bool is_mpu_begin = mpu.begin();
    bool is_mag_begin = mag.begin();
    bool is_lox_begin = lox.begin();
    Serial.print("mpu :");
    Serial.println(is_mpu_begin);
    Serial.print("mag :");
    Serial.println(is_mag_begin);
    Serial.print("lox :");
    Serial.println(is_lox_begin);
    
}

void loop() {
  
}
