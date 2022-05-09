#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "Adafruit_VL53L0X.h"

#include <FS.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>



#define R1 1000
#define R2 1000


ESP8266WebServer server(80);
WebSocketsServer webSocket(81);

Adafruit_MPU6050 mpu;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();




float get_voltage(){
    return (analogRead(A0)) / 1024 * (R1 + R2) / R2;    
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {
    return;
}



void start_WebSocket() {
  webSocket.begin();                         
  webSocket.onEvent(webSocketEvent);        
  Serial.println("WebSocket server started.");
}

bool start_mpu(){
    if(mpu.begin()){
        Serial.println("MPU is OK");
        return true;
    }
    Serial.println("MPU is FAILD");
    return false;
}

bool start_mag(){
    if(mag.begin()){
        Serial.println("MAG is OK");
    }
    Serial.println("MAG is FAILD");
    return false;
}

bool start_lox(){
    if(mpu.begin()){
        Serial.println("LOX is OK");
        return true;
    }
    Serial.println("LOX is FAILD");
    return false;
}









void setup() {
    Serial.begin(115200);
    WiFi.softAP("efs", "12345678");
    
    bool is_mpu_begin = start_mpu();
    bool is_mag_begin = start_mag();
    bool is_lox_begin = start_lox();
    
    start_WebSocket();
    

}

void loop() {
  
}


