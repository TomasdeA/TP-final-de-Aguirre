#ifndef PDC_H
#define PDC_H

#include "hcsr04.h"
#include "mbed.h"

extern bool pdcActiveState;  // Declarar pdcActiveState como variable externa


void pdcInit();
void pdcUpdate();

#endif  // PDC_H
