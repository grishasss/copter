#include "math_copter.h"

MATH::MATH(){
    
}

float MATH::get_acceleration(float new_angle , float tec_angle){
    return new_angle - tec_angle;
}


void MATH::calc_acro(){

}

void MATH::calc_auto(){
    float mn_A = Gg * mass / cos(Sensors->kren) / cos(Sensors->tangage);
    float to_3 = 4 * max_power - mn_A;
    float to_1 = to_3 / 3;
     
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
    mass = memory_get_float(2);
    moment_of_inertia1 = memory_get_float(6);
    moment_of_inertia2 = memory_get_float(10);
    len = memory_get_float(14);



}