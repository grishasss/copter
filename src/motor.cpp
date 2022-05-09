#include "motor.h"
// #include "ESP8266_PWM.h"

MOTORS::MOTORS(){

}
void MOTORS::stop(int MOTOR_ID){
    power[MOTOR_ID] = 0;
}

void MOTORS::stop_all(){

}
void MOTORS::set_power_to(int MOTOR_ID , int Power){
    power[MOTOR_ID] = Power;
}

void MOTORS::set_power_all(int Power[])
{
    
}
