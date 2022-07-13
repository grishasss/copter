#include "motor.h"



MOTORS::MOTORS(){

}
void MOTORS::begin(){
    for(uint8_t i = 0 ; i < 4 ; i++){
        pinMode(PWM_Pin[i], OUTPUT);
    }
}

void MOTORS::loop(){
    if(!is_on) return;
    for(uint8_t i = 0 ; i < 4 ; i++){
        analogWrite(PWM_Pin[i] ,power[i]);
    }
}

void MOTORS::stop_all(){
    is_on = false;
    
    for(uint8_t i = 0 ; i < 4 ; i++){
        analogWrite(PWM_Pin[i] ,0);
    }
}

void MOTORS::start_all(){
    is_on = true;
}



