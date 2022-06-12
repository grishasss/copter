#pragma once

#include "memory.h"


void MEMORY::init(){
    EEPROM.begin(512);
    SPIFFS.begin();
}

void MEMORY::write_bit(bool f , uint16_t pos){
    uint8_t ls = EEPROM.read(pos >> 3);
    uint8_t cnt_bit = 7 - pos % 8;
    ls ^= (ls & (1 << cnt_bit));
    ls |= ((uint8_t)f << cnt_bit); 
    EEPROM.write(pos >> 3 , ls);
    EEPROM.commit();
}

bool MEMORY::get_bit(uint16_t pos){
    uint8_t b = EEPROM.read(pos >> 3);
    uint8_t cnt_bit = 7 - pos % 8;
    return b & (1 << cnt_bit);
}