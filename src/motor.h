#pragma once

#include <Arduino.h>
#include "ESP8266_PWM.hpp"

#define MOTOR_1_PIN 1
#define MOTOR_2_PIN 2
#define MOTOR_3_PIN 3
#define MOTOR_4_PIN 4

class MOTORS{
    public:
    ESP8266_PWM ISR_PWM;
    MOTORS();
    int16_t power[4];
    
    
    void stop_all();
    void stop(int8_t MOTOR_ID);
    void set_power_to(int8_t MOTOR_ID , int16_t Power);    
    void set_power_all(int16_t Power[]);

};