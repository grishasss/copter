#include "motor.h"



MOTORS::MOTORS(){

}
void MOTORS::begin(){
    for(uint8_t i = 0 ; i < 4 ; i++){
        pinMode(PWM_Pin[i], OUTPUT);
    }
}

void MOTORS::loop(){
    for(uint8_t i = 0 ; i < 4 ; i++){
        analogWrite(PWM_Pin[i] ,power[i]);
    }
}
