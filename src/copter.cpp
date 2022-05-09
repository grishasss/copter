
#include "copter.h"
#include <EEPROM.h>
#include <FS.h>



#include "math_copter.h"
#include "web.h"
#include "sensors.h"


Copter::Copter(){

}


String file_name; 
SENSORS sensors;

void INIT(){
    Serial.begin(115200);
    SPIFFS.begin();
    EEPROM.begin(512);
    pinMode(A0, INPUT);
    // WiFi.softAP("efs", "12345678");
    bool is_mpu_begin = sensors.start_mpu();
    bool is_mag_begin = sensors.start_mag();
    bool is_lox_begin = sensors.start_lox();
    
}


void Copter::begin(){
    INIT();
    byte num_file = EEPROM.read(0);
    EEPROM.write(0 , num_file + 1);
    EEPROM.commit();
    file_name =String(num_file) + ".csv";
}


void Copter::process(){

}