//
// Created by Beau Barker on 4/22/2021.
//

#ifndef TEMPERATUREV2_WEBSERVER_H
#define TEMPERATUREV2_WEBSERVER_H

#include "TemperatureV2.h"
#include "Sensors.h"
#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>

class WebServer
{
private:
    uint8_t         mac[6] = {};
    char            read_buf[16] = {};
    EthernetServer  *server = nullptr;
    EthernetClient  client = EthernetClient();

public:
    WebServer(int csPin = 10, const uint8_t* macAddress = nullptr);

    const uint8_t* getMacAddress()
    {
        return mac;
    }

    bool startHosting();

    void maintain(Sensors* sensors);

private:
    int getRequest();
};

#endif //TEMPERATUREV2_WEBSERVER_H
