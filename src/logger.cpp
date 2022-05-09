#include "logger.h"
#include<Arduino.h>
#include <EEPROM.h>
#include <FS.h>

LOG::LOG(){

}

void LOG::write(){

}

void LOG::loop(){
    if(millis() - time_last_write < interval){
        write();
        time_last_write = millis();
    }
}