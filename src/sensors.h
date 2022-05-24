#pragma once

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "Adafruit_VL53L0X.h"
#include "math_copter.h"




#define R1 1000
#define R2 1000


// #define interval_sensors 100;
#define num_set_zero 10
#define pi 3.14
#define G 9.81
class SENSORS{
public:

    SENSORS();

    MATH* math;
    Adafruit_MPU6050 mpu;
    Adafruit_HMC5883_Unified mag;
    Adafruit_VL53L0X lox;

    float kren , tangage , yaw;
    float v_kren , v_tangage , v_yaw;
    
    float altitude;
    float voltage;

    int32_t time_last_update = 0;

    bool start_mpu();
    bool start_mag();
    bool start_lox();

    bool is_mpu_begin;
    bool is_mag_begin;
    bool is_lox_begin;

    void begin();
    float get_voltage();
    void loop();
    void mpu_set_zero();
    void mpu_calibrate(); // tmp not avibale
    float get_altitude();
};