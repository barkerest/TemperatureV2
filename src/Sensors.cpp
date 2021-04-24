//
// Created by Beau Barker on 4/23/2021.
//

#include "Sensors.h"


Sensors::Sensors(int channelA, int channelB) {
    wire[0] = new OneWire(channelA);
    wire[1] = new OneWire(channelB);
    channel[0] = new DallasTemperature(wire[0]);
    channel[0]->begin();
    channel[1] = new DallasTemperature(wire[1]);
    channel[1]->begin();
    uint8_t count1 = channel[0]->getDeviceCount();
    uint8_t count2 = channel[1]->getDeviceCount();
    if (count1 < 1) {
        if (count2 < 1) {
            DEBUG_LOG("WARN: Did not locate any sensors.\r\n");
            deviceChannel[0] = deviceChannel[1] = nullptr;
        } else if (count2 == 1) {
            DEBUG_LOG("INFO: Found sensor A on channel B.\r\n");
            DEBUG_LOG("WARN: Did not locate sensor B.\r\n");
            deviceChannel[0] = channel[1];
            channel[1]->getAddress(deviceAddress[0], 0);
            deviceChannel[1] = nullptr;
        } else {
            DEBUG_LOG("INFO: Found sensors A & B on channel B.\r\n");
            deviceChannel[0] = deviceChannel[1] = channel[1];
            channel[1]->getAddress(deviceAddress[0], 0);
            channel[1]->getAddress(deviceAddress[1], 1);
        }
    } else if (count1 == 1) {
        DEBUG_LOG("INFO: Found sensor A on channel A.\r\n");
        deviceChannel[0] = channel[0];
        channel[0]->getAddress(deviceAddress[0], 0);

        if (count2 < 1) {
            DEBUG_LOG("WARN: Did not locate sensor B.\r\n");
            deviceChannel[1] = nullptr;
        } else {
            DEBUG_LOG("INFO: Found sensor B on channel B.\r\n");
            deviceChannel[1] = channel[1];
            channel[1]->getAddress(deviceAddress[1], 0);
        }
    } else if (count1 >= 2) {
        DEBUG_LOG("INFO: Found sensors A & B on channel A.\r\n");
        deviceChannel[0] = deviceChannel[1] = channel[0];
        channel[0]->getAddress(deviceAddress[0], 0);
        channel[0]->getAddress(deviceAddress[1], 1);
    }

    lastMS = millis();
    pollDelay = 2000;
}

void Sensors::maintain() {
    uint32_t ms = millis();
    uint16_t elapsed;

    if (lastMS == ms) return;   // nothing to do if this gets called more than once in the same millisecond.

    if (ms < lastMS) {
        // when the timer rolls over, we need to adjust our elapsed value.
        elapsed = (uint16_t) (0xFFFFFFFF - lastMS) + (uint16_t) ms + 1;
    } else {
        // normally we can just subtract.
        elapsed = ms - lastMS;
    }

    if (elapsed >= pollDelay) {
        if (deviceChannel[0]) {
            deviceChannel[0]->requestTemperatures();
        }
        if (deviceChannel[1] && deviceChannel[1] != deviceChannel[0]) {
            deviceChannel[1]->requestTemperatures();
        }

        if (deviceChannel[0]) {
            a = (uint16_t) (((uint32_t) deviceChannel[0]->getTemp(deviceAddress[0]) * 10) / 128);
        }
        if (deviceChannel[1]) {
            b = (uint16_t) (((uint32_t) deviceChannel[1]->getTemp(deviceAddress[1]) * 10) / 128);
        }

        DEBUG_LOG("T1: ");
        DEBUG_LOG(Formatter::format_decimal(a, 1, 'C'));
        DEBUG_LOG("\r\nT2: ");
        DEBUG_LOG(Formatter::format_decimal(b, 1, 'C'));
        DEBUG_LOG("\r\n");

        pollDelay = 2000;
    } else {
        pollDelay -= elapsed;
    }

    lastMS = ms;
}
