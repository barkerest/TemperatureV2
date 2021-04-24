//
// Created by Beau Barker on 4/22/2021.
//

#include "Formatter.h"

#define FORMATTER_BUF_S     20

char _internal_buf[FORMATTER_BUF_S] = {};

#define MIN_N_FOR_VALUE32()     \
    ((value > 1000000000 ? 11 : \
    (value > 100000000 ? 10 :   \
    (value > 10000000 ? 9 :     \
    (value > 1000000 ? 8 :      \
    (value > 100000 ? 7 :       \
    (value > 10000 ? 6 :        \
    (value > 1000 ? 5 :         \
    (value > 100 ? 4 :          \
    (value > 10 ? 3 :           \
    2))))))))) +                \
    (prec ? 2 : 0) +            \
    (mark ? 1 : 0))

#define MIN_N_FOR_VALUE16()     \
    ((value > 10000 ? 6 :       \
    (value > 1000 ? 5 :         \
    (value > 100 ? 4 :          \
    (value > 10 ? 3 :           \
    2)))) +                     \
    (prec ? 2 : 0) +            \
    (mark ? 1 : 0))

#define MIN_N_FOR_VALUE8()      \
    ((value > 100 ? 4 :         \
    (value > 10 ? 3 :           \
    2)) +                       \
    (prec ? 2 : 0) +            \
    (mark ? 1 : 0))


#define CHECK_S()       if (!s){s = _internal_buf; n=FORMATTER_BUF_S;} else if (n < 1) return nullptr

#define FORMAT_DECIMAL()        \
if (1) {                        \
    if (n < min_n) {            \
        *s = 0;                 \
        return s;               \
    }                           \
    ptr = s + n - 1;            \
    *ptr = 0;                   \
    ptr--;                      \
    if (mark) {                 \
        *ptr = mark;            \
        ptr--;                  \
    }                           \
    *ptr = '0' + (value % 10);  \
    value /= 10;                \
    while (value > 0 || prec > 0) { \
        if (prec == 1) {        \
            ptr--;              \
            *ptr = '.';         \
            prec = 0;           \
        } else if (prec > 1) {  \
            prec--;             \
        }                       \
        ptr--;                  \
        *ptr = '0' + (value % 10);  \
        value /= 10;            \
    }                           \
} else return nullptr


const char *Formatter::format_decimal(uint32_t value, uint8_t prec, char mark, char *s, uint8_t n) {
    int min_n = MIN_N_FOR_VALUE32();
    char *ptr;

    CHECK_S();
    if (prec > 8) return nullptr;

    FORMAT_DECIMAL();

    return ptr;
}

const char *Formatter::format_decimal(int32_t value, uint8_t prec, char mark, char *s, uint8_t n) {
    int sign = value < 1 ? 1 : 0;
    if (sign) value *= -1;
    int min_n = MIN_N_FOR_VALUE32() + sign;
    char *ptr;

    CHECK_S();
    if (prec > 8) return nullptr;

    FORMAT_DECIMAL();

    if (sign)
    {
        ptr--;
        *ptr = '-';
    }

    return ptr;
}

const char *Formatter::format_decimal(uint16_t value, uint8_t prec, char mark, char *s, uint8_t n) {
    int min_n = MIN_N_FOR_VALUE16();
    char *ptr;

    CHECK_S();
    if (prec > 4) return nullptr;

    FORMAT_DECIMAL();

    return ptr;
}

const char *Formatter::format_decimal(int16_t value, uint8_t prec, char mark, char *s, uint8_t n) {
    int sign = value < 1 ? 1 : 0;
    if (sign) value *= -1;
    int min_n = MIN_N_FOR_VALUE16() + sign;
    char *ptr;

    CHECK_S();
    if (prec > 8) return nullptr;

    FORMAT_DECIMAL();

    if (sign)
    {
        ptr--;
        *ptr = '-';
    }

    return ptr;
}

const char *Formatter::format_decimal(uint8_t value, uint8_t prec, char mark, char *s, uint8_t n) {
    int min_n = MIN_N_FOR_VALUE8();
    char *ptr;

    CHECK_S();
    if (prec > 2) return nullptr;

    FORMAT_DECIMAL();

    return ptr;
}

const char *Formatter::format_decimal(int8_t value, uint8_t prec, char mark, char *s, uint8_t n) {
    int sign = value < 1 ? 1 : 0;
    if (sign) value *= -1;
    int min_n = MIN_N_FOR_VALUE8() + sign;
    char *ptr;

    CHECK_S();
    if (prec > 8) return nullptr;

    FORMAT_DECIMAL();

    if (sign)
    {
        ptr--;
        *ptr = '-';
    }

    return ptr;
}


inline char* hex_byte(uint8_t value, char* ptr)
{
    uint8_t nib = value & 0xF;
    ptr--;
    if (nib < 10)
    {
        *ptr = '0' + nib;
    }
    else
    {
        *ptr = 'A' + (nib - 10);
    }
    nib = (value >> 4) & 0xF;
    ptr--;
    if (nib < 10)
    {
        *ptr = '0' + nib;
    }
    else
    {
        *ptr = 'A' + (nib - 10);
    }
    return ptr;
}

const char *Formatter::format_hex(uint8_t value, char *s, uint8_t n) {
    char *ptr;
    CHECK_S();
    if (n < 3) return nullptr;

    ptr = s + n - 1;
    *ptr = 0;

    ptr = hex_byte(value, ptr);

    return ptr;
}

const char *Formatter::format_hex(uint8_t *value, uint8_t len, char sep, char *s, uint8_t n) {
    char *ptr;
    CHECK_S();
    int min_n = 1 + (len * 2) + (sep ? (len - 1) : 0);
    if (n < min_n) return nullptr;

    ptr = s + n - 1;
    *ptr = 0;

    uint8_t i = len - 1;
    while(true)
    {
        ptr = hex_byte(value[i], ptr);
        if (i > 0 && sep)
        {
            ptr--;
            *ptr = sep;
        }

        if (i == 0) break;
        i--;
    }

    return ptr;
}

