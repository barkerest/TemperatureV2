//
// Created by Beau Barker on 4/22/2021.
//

#ifndef TEMPERATUREV2_SENSORS_H
#define TEMPERATUREV2_SENSORS_H

#include "TemperatureV2.h"
#include <DallasTemperature.h>


class Sensors {
private:
    OneWire* wire[2] = {};
    DallasTemperature* channel[2] = {};
    DallasTemperature* deviceChannel[2] = {};
    DeviceAddress deviceAddress[2] = {};
    uint32_t lastMS = 0;     // ms at last maintain() call.
    uint16_t pollDelay = 0;  // ms until next poll.
    uint16_t a = 0;
    uint16_t b = 0;

public:
    Sensors(int channelA, int channelB);

    void maintain();

    // return the temperature in tenths of a degree Celsius (eg - 235 = 23.5C)
    uint16_t getTemperatureA() { return a; }

    uint16_t getTemperatureB() { return b; }
};


#endif //TEMPERATUREV2_SENSORS_H
