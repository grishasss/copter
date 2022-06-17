#include "motor.h"

MOTORS::MOTORS(){

}


void IRAM_ATTR MOTORS::TimerHandler(){
   c++;
}

void MOTORS::begin(){
    // if (ITimer.attachInterruptInterval(20L, std::bind(&MOTORS::TimerHandler))){
    //     Serial.print(F("Starting ITimer OK, micros() = ")); Serial.println(micros());
    // }
    // else
    //     Serial.println(F("Can't set ITimer. Select another freq. or timer"));
}

void MOTORS::stop_all(){
    
}
