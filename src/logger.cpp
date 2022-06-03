#include "logger.h"
#include<Arduino.h>
#include <EEPROM.h>
#include <FS.h>



LOG::LOG(){
    
    
}

void LOG::open_file(){
    
    if(Sensors->date[0] < 10) file_name+= '0' + String(Sensors->date[0]);
    else file_name+= String(Sensors->date[0]);
    file_name +='.';
    
    if(Sensors->date[1] < 10) file_name+= '0' + String(Sensors->date[1]);
    else file_name+= String(Sensors->date[1]);
    file_name +='-';

    if(Sensors->date[3] < 10) file_name+= '0' + String(Sensors->date[3]);
    else file_name+= String(Sensors->date[3]);
    file_name +=':';
    
    if(Sensors->date[4] < 10) file_name+= '0' + String(Sensors->date[4]);
    else file_name+= String(Sensors->date[4]);
    file_name +=".csv";

    file = SPIFFS.open("/" + file_name , "w");
    Serial.println("write log to: " + file_name);

}

void LOG::write(){
    Sensors->time_recalc();

    // String cnt_h();
    // String cnt_m((int16_t)(millis() / 1000 / 60) % 60);
    // String cnt_s((int32_t)(millis() / 1000) % 60);
    // if(cnt_h.length() < 2) cnt_h = "0" + cnt_h;
    // if(cnt_m.length() < 2) cnt_m = "0" + cnt_m;
    // if(cnt_s.length() < 2) cnt_s = "0" + cnt_s;
    // String time = cnt_h + ":" + cnt_m + ":" + cnt_s;
}

void LOG::loop(){
    if(Sensors->date_is_ccorrect){
        if(millis() - time_last_write < interval){
            write();
            time_last_write = millis();
        }
    }

}