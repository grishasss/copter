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
    file_name ="/log/" + file_name + ".csv";

    file = SPIFFS.open(file_name , "w");
    Serial.println("write log to: " + file_name);
    file.write(header);
    file.close();
}

void LOG::write(){
    Sensors->time_recalc();
    String T;
    if(Sensors->date[3] < 10) T+= '0' + String(Sensors->date[3]);
    else T+= String(Sensors->date[3]);
    T +=':';
    
    if(Sensors->date[4] < 10) T+= '0' + String(Sensors->date[4]);
    else T+= String(Sensors->date[4]);

    T+=':';

    if(Sensors->date[5] < 10) T+= '0' + String(Sensors->date[5]);
    else T+= String(Sensors->date[5]);

    T+=':';

    if(Sensors->date[6]  < 10) T+= '0' + String(Sensors->date[6]);
    else T+= String(Sensors->date[6]);
    T+='0';
    // Serial.println(T);
    file = SPIFFS.open(file_name , "a");
    file.print(T + '\n');
    file.close();
}

void LOG::loop(){
    if(Sensors->date_is_ccorrect){
        if(millis() - time_last_write > interval){
            write();
            time_last_write = millis();
        }
    }

}