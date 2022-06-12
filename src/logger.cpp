#include "logger.h"
#include<Arduino.h>
#include <EEPROM.h>
#include <FS.h>



LOG::LOG(){
    
    
}

void LOG::write_int(int32_t val , uint8_t cnt_bit){
    int8_t otstup = 0;
    if(val < 0) {
        packet[pos_to_write - ls_pos] = 1;
        val += (1  << (cnt_bit - 1));
        otstup = 1;
    }

    for(uint8_t i  = 0 ; i < cnt_bit - otstup; i++){
        packet[pos_to_write + cnt_bit - i - 1 - ls_pos] = (val & (1ll << i));
    }
    pos_to_write +=cnt_bit;
}

void LOG::open_file(){
    
    if(Sensors->date.day < 10) file_name+= '0' + String(Sensors->date.day);
    else file_name+= String(Sensors->date.day);
    file_name +='.';
    
    if(Sensors->date.mounth < 10) file_name+= '0' + String(Sensors->date.mounth);
    else file_name+= String(Sensors->date.mounth);
    file_name +='-';

    if(Sensors->date.hour < 10) file_name+= '0' + String(Sensors->date.hour);
    else file_name+= String(Sensors->date.hour);
    file_name +=':';

    if(Sensors->date.minute < 10) file_name+= '0' + String(Sensors->date.minute);
    else file_name+= String(Sensors->date.minute);
    file_name +=':';

    if(Sensors->date.second < 10) file_name+= '0' + String(Sensors->date.second);
    else file_name+= String(Sensors->date.second);
    

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
    
    
    write_int(Sensors->joy1X , 8);
    write_int(Sensors->joy1Y , 8);
    write_int(Sensors->joy2X , 8);
    write_int(Sensors->joy2Y , 8);


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
    // Sensors->time_recalc_big();
    // Serial.println(Sensors->date[4]);
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

