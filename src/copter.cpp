
#include "copter.h"
#include <EEPROM.h>
#include <FS.h>



#include "math_copter.h"
#include "web.h"
#include "sensors.h"
#include "motor.h"
#include "logger.h"



Copter::Copter(){

}


String file_name; 
SENSORS sensors;
WEB web;
LOG Log;

void INIT(){
    Serial.begin(115200);
    SPIFFS.begin();
    EEPROM.begin(512);
    sensors.begin();
}


void Copter::begin(){
    INIT();
    
}


void Copter::process(){
    web.loop();
    Log.loop();
}