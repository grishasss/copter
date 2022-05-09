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
    int power[5];
    
    
    void stop_all();
    void stop(int MOTOR_ID);
    void set_power_to(int MOTOR_ID , int Power);    
    void set_power_all(int Power[]);

};