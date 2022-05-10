#include "logger.h"
#include<Arduino.h>
#include <EEPROM.h>
#include <FS.h>

LOG::LOG(){
    byte num_file = EEPROM.read(0);
    EEPROM.write(0 , num_file + 1);
    EEPROM.commit();
    file_name = String(num_file) + ".csv";
}

void LOG::write(){

}

void LOG::loop(){
    if(millis() - time_last_write < interval){
        write();
        time_last_write = millis();
    }
}