#pragma once

#include<Arduino.h>
#include <FS.h>
#include "math_copter.h"
#include "sensors.h"
class LOG{
    public:
    
    LOG(); 
    SENSORS *Sensors;
    const char* header = "Date,voltage,altitude, \n";
    MATH* math;
    long time_last_write = 0;
    int interval = 100;
    bool is_writing = 0;
    File file;
    bool it_big = 1;
    String file_name;
    void open_file();
    void write_full();
    void write_little();
    
    void loop();
};
