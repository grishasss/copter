#pragma once

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "Adafruit_VL53L0X.h"





#define R1 1000
#define R2 1000


// #define interval_sensors 100
#define num_set_zero 10
#define pi 3.14
#define Gg 9.81


class Date{
public:
    uint8_t day , mounth , year , hour , minute , second , millis10;
};


class SENSORS{
public:

    SENSORS();

    
    Adafruit_MPU6050 mpu;
    Adafruit_HMC5883_Unified mag;
    Adafruit_VL53L0X lox;

    float kren , tangage , yaw;
    float v_kren , v_tangage , v_yaw;
    
    int32_t amendment;
    Date date;
    int16_t joy1X;
    int16_t joy1Y;
    int16_t joy2X;
    int16_t joy2Y;
    
    bool date_is_ccorrect = 0;


    int16_t altitude;
    float voltage;
    uint32_t time_begin_day;
    uint32_t time_last_update = 0;
    uint32_t time_last_voltage = 0;
    bool start_mpu();
    bool start_mag();
    bool start_lox();

    bool is_mpu_begin;
    bool is_mag_begin;
    bool is_lox_begin;

    void begin();
    void get_voltage();
    void loop();
    void mpu_set_zero();
    void mpu_calibrate(); // tmp not avibale
    float get_altitude();

    void time_recalc_small();
    void time_recalc_big();
    void get_value();
    void norm_angle(float &angle);
};