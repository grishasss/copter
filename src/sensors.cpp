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
    mpu_set_zero();
    mpu_calibrate();
}

bool SENSORS::start_mpu(){
    uint32_t st = millis();
    while(!mpu.begin() && millis() - st < 200);
    
    if(mpu.begin()){
        is_mpu_begin = 1;
        Serial.println("MPU is OK");
        mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
        mpu.setGyroRange(MPU6050_RANGE_500_DEG);
        mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
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
        // lox.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY);
        lox.setMeasurementTimingBudgetMicroSeconds((uint32_t)1e4);
        return true;
    }
    Serial.println("LOX is FAILD");
    return false;
}

void SENSORS::get_voltage(){
    if(millis() - time_last_voltage < 90) return;
    time_last_voltage = millis();
    voltage = analogRead(A0) /  (float)1024 * (R1 + R2) / R2;    
}
void SENSORS::mpu_set_zero(uint16_t cnt, uint16_t interval){

    if(!is_mpu_begin) return;
    Serial.println("start set zero");
    sensors_event_t a, g, temp;
    float srX = 0 , srY  = 0;
    for(int i = 0 ; i < cnt ; i++){
        mpu.getEvent(&a, &g, &temp);
        srX+=a.acceleration.x;
        srY+=a.acceleration.y;
        delay(interval);
    }
    srX /= cnt;
    srY /= cnt;
    tangage = acos(srX / Gg) - pi / 2;
    kren = acos(srY / Gg) - pi / 2;
    yaw = 0;
    time_last_update = micros();
    v_kren = g.gyro.y;
    v_tangage = g.gyro.x;
    v_yaw = g.gyro.z;

    Serial.println("OK");
    Serial.print("tangage: ");
    Serial.println(tangage);
    Serial.print("kren: ");
    Serial.println(kren);
}


void SENSORS::mpu_calibrate(uint16_t cnt , uint16_t interval){
    if(!is_mpu_begin) return;
    float srX = 0, srY = 0 , srZ = 0;
    Serial.println("start calibrate");
    sensors_event_t a, g, temp;
    for(int i = 0 ; i < cnt ; i++){
        mpu.getEvent(&a, &g, &temp);
        srX+=g.gyro.x;
        srY+=g.gyro.y;
        srZ+=g.gyro.z;
        delay(interval);
    }
    errX = srX / cnt;
    errY = srY / cnt;
    errZ = srZ / cnt;

    Serial.println("OK");
    Serial.print("errX: ");
    Serial.println(errX);
    
    Serial.print("errY: ");
    Serial.println(errY);
    
    Serial.print("errZ: ");
    Serial.println(errZ);
}
    


void SENSORS::loop(){
    sensors_event_t a, g, temp; 
    if(is_mpu_begin){
        
        mpu.getEvent(&a, &g, &temp);
        tangage += (v_tangage + g.gyro.x - errX) / 2 * (micros() - time_last_update) / 1e5;
        kren += (v_kren + g.gyro.y - errY) / 2 * (micros() - time_last_update) / 1e5;
        yaw += (v_yaw + g.gyro.z - errZ) / 2 * (micros() - time_last_update) / 1e5;
        // norm_angle(tangage);
        // norm_angle(kren);
        // norm_angle(yaw);
       
        v_tangage = g.gyro.x - errX;
        v_kren = g.gyro.y - errY;
        v_yaw = g.gyro.z - errZ;
        
        // v_tangage = 0;
        // v_kren = 0;
        // v_yaw = 0;

    }
    
    if(is_lox_begin){
        VL53L0X_RangingMeasurementData_t measure;
        if(measure.RangeStatus != 4){
            lox.rangingTest(&measure, false);
            altitude = measure.RangeMilliMeter;
        }
    }
    time_last_update = micros();
    get_voltage();
    
    // Serial.print(g.gyro.x);
    // Serial.print(" ");
    // Serial.print(g.gyro.y);
    // Serial.print(" ");
    // Serial.println(g.gyro.z);
    // Serial.print(" ");
    // Serial.print(a.acceleration.x);
    // Serial.print(" ");
    // Serial.println(a.acceleration.y);
    // Serial.print(" ");


    Serial.print(tangage);
    Serial.print(" ");
    Serial.print(kren);
    Serial.print(" ");
    Serial.println(yaw);
    // Serial.println(" ");

    // Serial.println(temp.temperature);
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
