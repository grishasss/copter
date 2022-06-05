#include "logger.h"
#include<Arduino.h>
#include <EEPROM.h>
#include <FS.h>



LOG::LOG(){
    
    
}

void LOG::write_int( int32_t val , uint8_t cnt_bit){
    for(uint8_t i  = 0 ; i < cnt_bit; i++){
        packet[pos_to_write + cnt_bit - i - 1] = (val & (1ll << i));
    }
    pos_to_write +=cnt_bit;
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
    file_name ="/log/" + file_name + ".bin";

    file = SPIFFS.open(file_name , "w");
    Serial.println("write log to: " + file_name);
    // file.write(header);
    file.close();
}

void LOG::write_full(){
    Sensors->time_recalc_big();
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

void LOG::write_small(){
    Sensors->time_recalc_small();
    pos_to_write = 0;
    write_int(Sensors->time_begin_day , 27);
    write_int(analogRead(A0) , 10);
    write_int(Sensors->altitude, 11);
    

    for(int8_t i = 0 ; i < 4 ; i++){
        write_int(Sensors->joy_state[i] , 8);
    }


    write_int(Sensors->tangage * 1024 / 2 / pi , 10);
    write_int(Sensors->kren * 1024 / 2 / pi , 10);
    write_int(Sensors->yaw * 1024 / 2 / pi , 10);
    
    for(uint8_t i = 0 ; i < 140 ; i+=8){
        packet_in_byte[i >> 3] = 0;
        for(uint8_t j = 0 ; j < 8 ; j++){
            packet_in_byte[i >> 3] |= (((uint8_t)packet[i + j]) << (8 - j)) ;
        }   
    }
    file = SPIFFS.open(file_name , "a");
    file.write((char*)packet_in_byte, 31);
    file.close();
}

void LOG::loop(){
    if(Sensors->date_is_ccorrect){
        if(millis() - time_last_write > interval){
            if(it_big)write_full();
            else write_small();
            time_last_write = millis();
        }
    }
}



// time 27
// voltage  10
// alt 11
// pos 8*4 = 32
// power 8*4 =32
// angle 3*10 = 30

