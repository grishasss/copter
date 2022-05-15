#include "logger.h"
#include<Arduino.h>
#include <EEPROM.h>
#include <FS.h>

LOG::LOG(){
    byte num_file = EEPROM.read(0);
    EEPROM.write(0 , num_file + 1);
    EEPROM.commit();
    file_name = String(num_file) + ".csv";
    file = SPIFFS.open("/" + file_name , "w");
    file.write(header);
}

void LOG::write(){
    String cnt_h(millis() / 1000 / 3600);
    String cnt_m(millis() / 1000 / 60);
    String cnt_s(millis() / 1000 );
    if(cnt_h.length() < 2) cnt_h = "0" + cnt_h;
    if(cnt_m.length() < 2) cnt_m = "0" + cnt_m;
    if(cnt_s.length() < 2) cnt_s = "0" + cnt_s;
    String time = cnt_h + ":" + cnt_m + ":" + cnt_s;
    
        
    
     
}

void LOG::loop(){
    if(millis() - time_last_write < interval){
        write();
        time_last_write = millis();
    }

}