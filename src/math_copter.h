#include <Arduino.h>

class MATH{
public:

    MATH();
    int16_t state_joy[4];
    
    float get_acceleration(float new_angle , float tec_angle);
    
};



