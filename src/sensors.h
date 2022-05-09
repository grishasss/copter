#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "Adafruit_VL53L0X.h"



#define R1 1000
#define R2 1000


class SENSORS{
public:

    SENSORS();


    Adafruit_MPU6050 mpu;
    Adafruit_HMC5883_Unified mag;
    Adafruit_VL53L0X lox;



    bool start_mpu();
    bool start_mag();
    bool start_lox();

    bool is_mpu_begin;
    bool is_mag_begin;
    bool is_lox_begin;

    void begin();
    float get_voltage();

};