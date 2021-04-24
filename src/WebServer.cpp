//
// Created by Beau Barker on 4/22/2021.
//

#include "WebServer.h"
#include <Wire.h>

#define I2C_ADDRESS 0x50

uint8_t readMacByte(uint8_t offset) {
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(offset);
    Wire.endTransmission();

    Wire.requestFrom(I2C_ADDRESS, 1);
    while (!Wire.available()) {}
    return Wire.read();
}


WebServer::WebServer(int csPin, const uint8_t *macAddress) {
    if (macAddress) {
        DEBUG_LOG("Using provided MAC address: ");
        mac[0] = macAddress[0];
        mac[1] = macAddress[1];
        mac[2] = macAddress[2];
        mac[3] = macAddress[3];
        mac[4] = macAddress[4];
        mac[5] = macAddress[5];
    } else {
        DEBUG_LOG("Using stored MAC address: ");
        Wire.begin();
        mac[0] = readMacByte(0xFA);
        mac[1] = readMacByte(0xFB);
        mac[2] = readMacByte(0xFC);
        mac[3] = readMacByte(0xFD);
        mac[4] = readMacByte(0xFE);
        mac[5] = readMacByte(0xFF);
    }
    DEBUG_LOG(Formatter::format_hex(mac, 6, '-'));
    DEBUG_LOG("\r\n");

    DEBUG_LOG("Using CS pin ");
    DEBUG_LOG(csPin);
    DEBUG_LOG(" to enable Ethernet.\r\n");
    EthernetClass::init(csPin);
}

bool WebServer::startHosting() {
    if (server) return true;

    if (Ethernet.begin(mac) == 0) {
        DEBUG_LOG("Failed to initialize Ethernet with DHCP.\r\n");
        return false;
    }
    DEBUG_LOG("Initialized Ethernet with DHCP.\r\nIP Address: ");
    DEBUG_LOG(Ethernet.localIP());
    DEBUG_LOG("\r\n");

    server = new EthernetServer(80);
    server->begin();
    DEBUG_LOG("Hosting started on port 80.\r\n");

    return true;
}

void WebServer::maintain(Sensors* sensors) {
    if (server) {
        switch (Ethernet.maintain()) {
            case 1:     // renew fail
                DEBUG_LOG("Ethernet Error: renewal failed\r\n");
                break;
            case 2:     // renew success
                DEBUG_LOG("Ethernet Notice: renewal succeeded\r\n");
                break;
            case 3:     // rebind fail
                DEBUG_LOG("Ethernet Error: rebind failed\r\n");
                break;
            case 4:     // rebind success
                DEBUG_LOG("Ethernet Notice: rebind succeeded (");
                DEBUG_LOG(Ethernet.localIP());
                DEBUG_LOG(")\r\n");
                break;
            default:
                break;
        };

        int req = getRequest();
        if (client && client.connected()) {
            if (req >= 1) {
                DEBUG_LOG("Sending response...\r\n");
                // send headers.
                client.println("HTTP/1.1 200 OK");
                client.println("Content-Type: text/plain");
                client.println("Connection: close");
                client.println("Cache-Control: no-cache");
                client.println();

                // return temperatures.
                client.print("T1: ");
                client.println(Formatter::format_decimal(sensors->getTemperatureA(),1,'C'));
                client.print("T2: ");
                client.println(Formatter::format_decimal(sensors->getTemperatureB(),1,'C'));
            }
            if (req == 2) {
                // return MAC & version.
                client.print("MAC: ");
                client.println(Formatter::format_hex(mac,6,'-'));
                client.print("VER: ");
                client.println(TEMPERATURE_VERSION);
            }

            delay(1);
            client.stop();
        }
    } else {
        startHosting();
    }
}

int WebServer::getRequest() {
    bool blank_line = true;
    char ch;
    uint8_t read_index = 0;
    uint8_t request_step = 3;
    uint16_t result = 200;
    uint8_t max_read_ix = sizeof(read_buf) - 1;
    int ret = 0;

    client = server->available();

    if (!client) return 0;
    DEBUG_LOG("Connection from ");
    DEBUG_LOG(client.remoteIP());
    DEBUG_LOG("\r\n");

    while (client.connected()) {
        if (client.available()) {
            ch = client.read();
            if (ch == '\n' && blank_line) break;    // end of request.
            if (ch == '\r') continue;               // ignore CR

            // anything other than a newline character means we don't have a blank line for the next iteration.
            blank_line = (ch == '\n');

            // if we finished processing the first line, we have nothing else to process in the request.
            if (!request_step) continue;

            // space and newline are our delimiters.
            if (ch == ' ' || ch == '\n') {
                switch (request_step) {
                    case 3:
                        if (ch == '\n') {
                            result = 400;
                            request_step = 0;
                        } else {
                            if (!strcmp(read_buf, "GET")) {
                                request_step = 2;
                            } else {
                                result = 405;
                                request_step = 0;
                            }
                        }
                        break;
                    case 2:
                        if (ch == '\n') {
                            result = 400;
                            request_step = 0;
                        } else {
                            if (!strcmp(read_buf, "/")) {
                                request_step = 1;
                                ret = 1;
                            } else if (!strcmp(read_buf, "/v")) {
                                request_step = 1;
                                ret = 2;
                            } else {
                                result = 404;
                                request_step = 0;
                            }
                        }
                        break;
                    case 1:
                        if (ch != '\n') {
                            result = 400;
                        }
                        request_step = 0;
                        break;
                    default:
                        break;
                }
                read_index = 0;
            } else if (read_index < max_read_ix) {
                // append the character and then a nul byte.
                read_buf[read_index] = ch;
                read_index++;
                read_buf[read_index] = 0;
            } else {
                DEBUG_LOG("BUFFER OVERFLOW\r\n");
                switch (request_step) {
                    case 3: // method
                        result = 405;
                        break;
                    case 2: // URI
                        result = 404;
                        break;
                    case 1: // version
                        result = 400;
                        break;
                    default: // should never happen.
                        result = 500;
                        break;
                }
            }
        }
    }

    if (client.connected() && result != 200) {
        ret = 0;

        DEBUG_LOG("Sending error response...\r\n");
        client.print("HTTP/1.1 ");
        client.print(result);
        client.println(" ERROR");
        client.println("Connection: close");
        client.println();
    }

    return ret;
}

