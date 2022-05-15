#include "sensors.h"


#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "Adafruit_VL53L0X.h"


SENSORS::SENSORS(){
    
}

void SENSORS::begin(){
    pinMode(A0, INPUT);
    start_mpu();
    start_mag();
    start_lox();
}

bool SENSORS::start_mpu(){
    if(mpu.begin()){
        is_mpu_begin = 1;
        Serial.println("MPU is OK");
        return true;
    }
    Serial.println("MPU is FAILD");
    return false;
}

bool SENSORS::start_mag(){
    if(mag.begin()){
        is_mag_begin = 1;
        Serial.println("MAG is OK");
        return true;
    }
    Serial.println("MAG is FAILD");
    return false;
}

bool SENSORS::start_lox(){
    if(mpu.begin()){
        is_lox_begin = 1;
        Serial.println("LOX is OK");
        return true;
    }
    Serial.println("LOX is FAILD");
    return false;
}

float SENSORS::get_voltage(){
    return (analogRead(A0)) / 1024 * (R1 + R2) / R2;    
}
void SENSORS::mpu_set_zero(){
    sensors_event_t a, g, temp;
    float srX = 0 , srY  = 0;
    for(int count = 0 ; count < num_set_zero ; count++){
        mpu.getEvent(&a, &g, &temp);
        srX+=a.acceleration.x;
        srY+=a.acceleration.y;
        delay(150);
    }
    srX /= num_set_zero;
    srY /= num_set_zero;
    tangage = acos(srX / G) - pi / 2;
    kren = acos(srY / G) - pi / 2;
    yaw = 0;
    time_last_update = millis();
    v_kren = g.gyro.y;
    v_tangage = g.gyro.x;
    v_yaw = g.gyro.z;
}

float SENSORS::get_altitude(){
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);
    return measure.RangeMilliMeter;
}


void SENSORS::loop(){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    tangage += (v_tangage + g.gyro.x) / 2 * (millis() - time_last_update) / 1000;
    kren += (v_kren + g.gyro.y) / 2 * (millis() - time_last_update) / 1000;
    yaw += (v_yaw + g.gyro.z) / 2 * (millis() - time_last_update) / 1000;
    v_tangage = g.gyro.x;
    v_kren = g.gyro.y;
    v_yaw = g.gyro.z;
    time_last_update = millis();
    voltage = get_voltage();
    altitude = get_altitude();
    math->altitude = altitude;
    math->v_kren = v_kren;
    math->v_yaw = v_yaw;
    math->v_tangage = v_tangage;
    math->tangage = tangage;
    math->yaw = yaw;
    math->kren = kren;    
}



