//
// Created by Beau Barker on 4/22/2021.
//

#ifndef TEMPERATUREV2_FORMATTER_H
#define TEMPERATUREV2_FORMATTER_H

#include <cstdint>

class Formatter
{
public:
    static const char* format_decimal(uint32_t value, uint8_t prec=0, char mark=0, char* s = nullptr, uint8_t n = 0);

    static const char* format_decimal(int32_t value, uint8_t prec=0, char mark=0, char* s = nullptr, uint8_t n = 0);

    static const char* format_decimal(uint16_t value, uint8_t prec=0, char mark=0, char* s = nullptr, uint8_t n = 0);

    static const char* format_decimal(int16_t value, uint8_t prec=0, char mark=0, char* s = nullptr, uint8_t n = 0);

    static const char* format_decimal(uint8_t value, uint8_t prec=0, char mark=0, char* s = nullptr, uint8_t n = 0);

    static const char* format_decimal(int8_t value, uint8_t prec=0, char mark=0, char* s = nullptr, uint8_t n = 0);

    static const char* format_hex(uint8_t value, char* s = nullptr, uint8_t n = 0);

    static const char* format_hex(uint8_t* value, uint8_t len, char sep = 0, char* s = nullptr, uint8_t n = 0);

    static const char* format_hex(uint16_t value, char sep = 0, char* s = nullptr, uint8_t n = 0)
    {
        return format_hex((uint8_t*)&value, 2, sep, s, n);
    }

    static const char* format_hex(int16_t value, char sep = 0, char* s = nullptr, uint8_t n = 0)
    {
        return format_hex((uint8_t*)&value, 2, sep, s, n);
    }

    static const char* format_hex(uint32_t value, char sep = 0, char* s = nullptr, uint8_t n = 0)
    {
        return format_hex((uint8_t*)&value, 4, sep, s, n);
    }

    static const char* format_hex(int32_t value, char sep = 0, char* s = nullptr, uint8_t n = 0)
    {
        return format_hex((uint8_t*)&value, 4, sep, s, n);
    }

};


#endif //TEMPERATUREV2_FORMATTER_H
