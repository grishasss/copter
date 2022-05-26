
#include "copter.h"
#include <EEPROM.h>
#include <FS.h>



// #include "math_copter.h"
#include "web.h"
#include "sensors.h"
#include "motor.h"
#include "logger.h"



Copter::Copter(){

}


String file_name; 
SENSORS sensors;

LOG Log;
MATH math;
// WEB web;
WEB  web;
void INIT(){
    Serial.begin(115200);
    SPIFFS.begin();
    EEPROM.begin(512);
   
    sensors.begin();
    web.wifi_init();
    web.start_all_server();
}


void Copter::begin(){
    INIT();
    
    
}


void Copter::process(){
    web.loop();
    Log.loop();
}