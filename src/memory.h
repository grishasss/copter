#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <FS.h>

class MEMORY{
public:
    
    void init();
    void write_bit(bool f , uint16_t pos);
    void write_float(float f, uint16_t pos);
    void write_uint32(uint32_t f, uint16_t pos);
    void write_uint16(uint16_t f, uint16_t pos);
    
    bool get_bit(uint16_t pos);
    float get_float(uint16_t pos);
    uint16_t get_uint16(uint16_t pos);
    uint32_t get_uint32(uint16_t pos);
};