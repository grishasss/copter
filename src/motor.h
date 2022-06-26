#pragma once

#include <Arduino.h>



class MOTORS{
    public:
    MOTORS();
    
    

    bool is_on = 0;
    uint16_t power[4] = {128 , 128 , 128 , 128};
    uint8_t PWM_Pin[4] = {14 , 12 , 13 , 16};


    void begin();
    void stop_all();
    void start_all();
    void loop();
};