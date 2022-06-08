#include "logger.h"
#include<Arduino.h>
#include <EEPROM.h>
#include <FS.h>



LOG::LOG(){
    
    
}

void LOG::write_int(int32_t val , uint8_t cnt_bit){
    for(uint8_t i  = 0 ; i < cnt_bit; i++){
        packet[pos_to_write + cnt_bit - i - 1 - ls_pos] = (val & (1ll << i));
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
    file_name +=':';

    if(Sensors->date[5] < 10) file_name+= '0' + String(Sensors->date[5]);
    else file_name+= String(Sensors->date[5]);
    

    file_name ="/log/" + file_name + ".hex";

    file = SPIFFS.open(file_name , "w");
    file.close();
    Serial.println("write log to: " + file_name);
    // file.write(header);
    
}


void LOG::add_line(){
    ls_pos = pos_to_write;
    Sensors->time_recalc_small();
    write_int(Sensors->time_begin_day , 27);
    write_int(analogRead(A0) , 10);
    write_int(Sensors->altitude, 11);
    

    for(int8_t i = 0 ; i < 4 ; i++){
        write_int(Sensors->joy_state[i] , 8);
    }


    write_int(Sensors->tangage * 1024 / 2 / pi , 10);
    write_int(Sensors->kren * 1024 / 2 / pi , 10);
    write_int(Sensors->yaw * 1024 / 2 / pi , 10);
    

    write_int(0 , 2);        
    assert(pos_to_write % 8 == 0);

    for(uint16_t i = ls_pos ; i < pos_to_write ; i+=8){
        packet_in_byte[i >> 3] = 0;
        for(uint8_t j = 0 ; j < 8 ; j++){
            packet_in_byte[i >> 3] |= (((uint8_t)packet[i + j - ls_pos]) << (7 - j)) ;
        }
        // Serial.print(packet_in_byte[i >> 3]);
        // Serial.print(" ");

    }
    // Serial.println();
    line_cnt++;
}

void LOG::loop(){
     if(line_cnt >= max_line){
        file = SPIFFS.open(file_name , "a");
        Serial.println("write to file: " + String(pos_to_write));
        file.write(packet_in_byte , pos_to_write >> 3);
        file.close();
        line_cnt = 0;
        pos_to_write = 0;
    }

    if(Sensors->date_is_ccorrect){
        if(millis() - time_last_write > interval){
            add_line();
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

