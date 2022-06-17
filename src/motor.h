#pragma once

#include <Arduino.h>
#include "ESP8266_PWM.hpp"

#define MOTOR_1_PIN 1
#define MOTOR_2_PIN 2
#define MOTOR_3_PIN 3
#define MOTOR_4_PIN 4

#define USING_TIM_DIV1                true              // for shortest and most accurate timer
#define USING_TIM_DIV16               false             // for medium time and medium accurate timer
#define USING_TIM_DIV256              false

class MOTORS{
    public:
    
    ESP8266Timer ITimer;
    MOTORS();

    
    

    uint16_t power[4];
    uint8_t PWM_Pin[4] = {1};
    float Freq = 1000;
    uint32_t Period = 100;

    void begin();
    void stop_all();
    void loop();
    
private:
    void IRAM_ATTR TimerHandler();
    volatile ESP8266_PWM ISR_PWM;
    volatile int c = 0;
};