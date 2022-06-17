#include "math_copter.h"

MATH::MATH(){
    
}

float MATH::get_acceleration(float new_angle , float tec_angle){
    return new_angle - tec_angle;
}


void MATH::calc_acro(){

}

void MATH::calc_auto(){
    
}


void MATH::loop(){
    real_altitude = float(Sensors->altitude) * cos(Sensors->kren) * cos(Sensors->tangage);
    switch (mode){
    case 0:
        calc_acro();
        break;
    case 1:
        calc_auto();
    default:
        break;
    }
}


void MATH::recalc_base(){
    mass = Memory->get_float(2);
    moment_of_inertia1 = Memory->get_float(6);
    moment_of_inertia2 = Memory->get_float(10);
    len = Memory->get_float(14);


    
}