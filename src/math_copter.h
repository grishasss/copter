#pragma once

#include <Arduino.h>
#include "sensors.h"


class MATH{
public:
    SENSORS *Sensors;


    MATH();
    
    float get_acceleration(float new_angle , float tec_angle);
};



