#include "sensors.h"


#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "Adafruit_VL53L0X.h"

void  SENSORS::norm_angle(float &angle){
    while(angle < 0) angle+=2*pi;
    while(angle > 2*pi) angle-=2*pi;
}

SENSORS::SENSORS() : mag(12345){
    
}

void SENSORS::begin(){
    pinMode(A0, INPUT);
    start_mpu();
    start_mag();
    start_lox();
}

bool SENSORS::start_mpu(){
    uint32_t st = millis();
    while(!mpu.begin() && millis() - st < 200);
    
    if(mpu.begin()){
        is_mpu_begin = 1;
        Serial.println("MPU is OK");
        return true;
    }
    Serial.println("MPU is FAILD");
    return false;
}

bool SENSORS::start_mag(){
    uint32_t st = millis();
    while(!mag.begin() && millis() - st < 200);
    
    if(mag.begin()){
        is_mag_begin = 1;
        Serial.println("MAG is OK");
        return true;
    }
    Serial.println("MAG is FAILD");
    return false;
}

bool SENSORS::start_lox(){
    uint32_t st = millis();
    while(!lox.begin() && millis() - st < 200);
    
    if(lox.begin()){
        is_lox_begin = 1;
        Serial.println("LOX is OK");
        return true;
    }
    Serial.println("LOX is FAILD");
    return false;
}

void SENSORS::get_voltage(){
    if(millis() - time_last_voltage < 90) return;
    time_last_voltage = millis();
    voltage = analogRead(A0) / 1024 * (R1 + R2) / R2;    
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
    tangage = acos(srX / Gg) - pi / 2;
    kren = acos(srY / Gg) - pi / 2;
    yaw = 0;
    time_last_update = millis();
    v_kren = g.gyro.y;
    v_tangage = g.gyro.x;
    v_yaw = g.gyro.z;
}




void SENSORS::loop(){
    sensors_event_t a, g, temp;
    if(is_mpu_begin){
        
        mpu.getEvent(&a, &g, &temp);
        tangage += (v_tangage + g.gyro.x) / 2 * (millis() - time_last_update) / 1000;
        kren += (v_kren + g.gyro.y) / 2 * (millis() - time_last_update) / 1000;
        yaw += (v_yaw + g.gyro.z) / 2 * (millis() - time_last_update) / 1000;
        norm_angle(tangage);
        norm_angle(kren);
        norm_angle(yaw);
       
        v_tangage = g.gyro.x;
        v_kren = g.gyro.y;
        v_yaw = g.gyro.z;
    }
    
    if(is_lox_begin){
        VL53L0X_RangingMeasurementData_t measure;
        lox.rangingTest(&measure, false);
        altitude = measure.RangeMilliMeter;
        
    }
    time_last_update = millis();
    get_voltage();

    Serial.print(altitude);
    Serial.print(" ");
    Serial.println(temp.temperature);
}


void SENSORS::time_recalc_big(){
    time_begin_day = amendment + millis();
    date.hour = time_begin_day / 1000 / 3600;
    date.minute = time_begin_day / 1000 / 60 % 60;
    date.second =  time_begin_day / 1000 % 60;
    date.millis10 = time_begin_day % 1000 / 10;
}

void SENSORS::time_recalc_small(){
    time_begin_day = amendment + millis();
}
