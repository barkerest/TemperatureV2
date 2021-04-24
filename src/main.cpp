#include "TemperatureV2.h"
#include "Sensors.h"
#include "WebServer.h"

#define SENSOR_CHANNEL_A    5
#define SENSOR_CHANNEL_B    6
#define ETH_CS_PIN          10

Sensors *sensors;
WebServer *webServer;

void setup() {
    DEBUG_INIT();
    DEBUG_LOG("----------------\r\nTemperature V" TEMPERATURE_VERSION "\r\n----------------\r\n");

    sensors = new Sensors(SENSOR_CHANNEL_A, SENSOR_CHANNEL_B);
    webServer = new WebServer(ETH_CS_PIN);
}

void loop() {
    sensors->maintain();
    webServer->maintain(sensors);
}
