#include "copter.h"




Copter mycopter;


void setup() {
    mycopter.begin();
}

void loop() {
    mycopter.process();
}


