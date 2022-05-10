#include<Arduino.h>
#include <EEPROM.h>
#include <FS.h>

class LOG{
    public:

    LOG();
    long time_last_write = 0;
    int interval = 100;
    bool is_writing = 0;
    String file_name;

    void write();
    void loop();
};
