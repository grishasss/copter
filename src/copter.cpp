
#include "copter.h"
#include <EEPROM.h>
#include <FS.h>



// #include "math_copter.h"
#include "web.h"
#include "sensors.h"
#include "motor.h"
#include "logger.h"
#include "memory.h"


Copter::Copter(){

}


String file_name; 
SENSORS sensors;

LOG Log;
MATH math;
MEMORY memory;
WEB  web;
void INIT(){
    Serial.begin(115200);
    memory.init();

    web.Sensors = (&sensors);
    web.Log = (&Log);
    web.Memory = (&memory);
    Log.Sensors = (&sensors);
    Log.Memory = (&memory);
    
    web.wifi_init();
    sensors.begin();
    web.start_all_server();

}


void Copter::begin(){
    INIT();
    
    
}


void Copter::process(){
    web.loop();
    Log.loop();
}