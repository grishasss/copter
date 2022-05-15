#pragma once

#include<Arduino.h>
#include <EEPROM.h>
#include <FS.h>
#include "math_copter.h"

class LOG{
    public:
    
    LOG();
    const char* header = "";
    MATH* math;
    long time_last_write = 0;
    int interval = 100;
    bool is_writing = 0;
    File file;
    String file_name;

    void write();
    void loop();
};
