#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <FS.h>

class MEMORY{
public:
    
    void init();
    void write_bit(bool f , uint16_t pos);
    bool get_bit(uint16_t pos);
};