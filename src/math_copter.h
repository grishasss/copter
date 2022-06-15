#pragma once

#include <Arduino.h>
#include "sensors.h"


class MATH{
public:
    SENSORS *Sensors;


    MATH();

    uint8_t mode = 0;
    float real_altitude = 0;
    float get_acceleration(float new_angle , float tec_angle);
    void calc_acro();
    void calc_auto();
    void loop();
};



