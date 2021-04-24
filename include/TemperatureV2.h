//
// Created by Beau Barker on 4/22/2021.
//

#ifndef TEMPERATUREV2_TEMPERATUREV2_H
#define TEMPERATUREV2_TEMPERATUREV2_H

#include <Arduino.h>

#ifdef DEBUG
    #define DEBUG_INIT()    if (1) { uint32_t ms = millis() + 5000; Serial.begin(9600); while (!Serial && millis() < ms) {} } else 0
    #define DEBUG_LOG(m)    if (Serial) Serial.print(m)
#else
    #define DEBUG_INIT()
    #define DEBUG_LOG(m)
#endif

#define TEMPERATURE_VERSION "2.0"

#include "Formatter.h"


#endif //TEMPERATUREV2_TEMPERATUREV2_H
