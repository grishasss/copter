#include "math.h"

float get_acceleration(float new_angle , float tec_angle){
    return new_angle - tec_angle;
}
