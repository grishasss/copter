#pragma once

#include <Arduino.h>

class MATH{
public:

    MATH();
    int16_t state_joy[4];
    float kren , tangage , yaw;
    float v_kren , v_tangage , v_yaw;
    
    float altitude;
    float voltage;
    
    float get_acceleration(float new_angle , float tec_angle);
    
};



