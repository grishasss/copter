#include "sensors.h"


#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "Adafruit_VL53L0X.h"


SENSORS::SENSORS(){
    
}



bool SENSORS::start_mpu(){
    if(mpu.begin()){
        Serial.println("MPU is OK");
        return true;
    }
    Serial.println("MPU is FAILD");
    return false;
}

bool SENSORS::start_mag(){
    if(mag.begin()){
        Serial.println("MAG is OK");
    }
    Serial.println("MAG is FAILD");
    return false;
}

bool SENSORS::start_lox(){
    if(mpu.begin()){
        Serial.println("LOX is OK");
        return true;
    }
    Serial.println("LOX is FAILD");
    return false;
}

float SENSORS::get_voltage(){
    return (analogRead(A0)) / 1024 * (R1 + R2) / R2;    
}