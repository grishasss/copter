#pragma once

#include <Arduino.h>
#include "sensors.h"
#include "memory.h"


class MATH{
public:
    SENSORS *Sensors;

    MATH();



    uint8_t mode = 0;
    float real_altitude = 0;
    
    float mass = 0;
    float moment_of_inertia1 = 0;
    float moment_of_inertia2 = 0;
    float len = 500;
    float max_power = 0;
    
    float get_acceleration(float new_angle , float tec_angle);
    void calc_acro();
    void calc_auto();
    void loop();

    void set_defualt();
    void recalc_base();
};



