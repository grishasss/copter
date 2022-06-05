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
    bool packet[150];
    uint8_t packet_in_byte[150 / 5 + 1];
    uint8_t pos_to_write = 0;
    
    MATH* math;
    long time_last_write = 0;
    int interval = 100;
    bool is_writing = 0;
    File file;
    bool it_big = 0;
    String file_name;
    void open_file();
    void write_full();
    void write_small();
    void write_int(int32_t val , uint8_t cnt_bit);
    void loop();
};


// time 27
// voltage  9
// alt 8
// pos 8*4 = 32
// power 8*4 =32
// angle 3*10 = 30



