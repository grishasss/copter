#include "sensors.h"


#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "Adafruit_VL53L0X.h"


SENSORS::SENSORS(){
    
}

void SENSORS::begin(){
    pinMode(A0, INPUT);
    start_mpu();
    start_mag();
    start_lox();
}

bool SENSORS::start_mpu(){
    if(mpu.begin()){
        is_mpu_begin = 1;
        Serial.println("MPU is OK");
        return true;
    }
    Serial.println("MPU is FAILD");
    return false;
}

bool SENSORS::start_mag(){
    if(mag.begin()){
        is_mag_begin = 1;
        Serial.println("MAG is OK");
        return true;
    }
    Serial.println("MAG is FAILD");
    return false;
}

bool SENSORS::start_lox(){
    if(mpu.begin()){
        is_lox_begin = 1;
        Serial.println("LOX is OK");
        return true;
    }
    Serial.println("LOX is FAILD");
    return false;
}

float SENSORS::get_voltage(){
    return (analogRead(A0)) / 1024 * (R1 + R2) / R2;    
}