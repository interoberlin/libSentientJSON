/**
 * In dieser Datei sind die Datentypen und Methoden deklariert,
 * die benoetigt werden, um die Farbaenderungsmuster
 * der LEDs festzulegen und zu handhaben
 */

#ifndef PATTERN_H
#define PATTERN_H

#include <stdbool.h>
#include <stdint.h>

/**
 * This struct/type holds information for
 * the behaviour of one LED channel
 * (every LED has three channels)
 */
struct pattern_s
{
    bool enabled:1;         // enable/disable this pattern
    uint32_t repetitions;   // number of iterations (timer ISR invokations) after which this pattern is disabled
    uint8_t final;          // value to be assigned at the end of this pattern
    float current;          // the current value of this pattern's channel (with decimal places)
    float increment;        // how much the current value is to be incremented/decremented in every step
};
typedef struct pattern_s pattern_t;

#endif
