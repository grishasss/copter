#include "math_copter.h"

MATH::MATH(){
    
}

float MATH::get_acceleration(float new_angle , float tec_angle){
    return new_angle - tec_angle;
}
