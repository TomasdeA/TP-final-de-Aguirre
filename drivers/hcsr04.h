// hcsr04.h

#ifndef HCSR04_H
#define HCSR04_H

#include "mbed.h"

class HCSR04 {
public:
    HCSR04(DigitalOut triggerPin, DigitalIn echoPin);
    float distance();

private:
    DigitalOut trigger;
    DigitalIn echo;
};

#endif  // HCSR04_H
