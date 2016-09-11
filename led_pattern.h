/**
 * This file declares types and methods,
 * which control the change of LED colors/values over time
 */

#ifndef PATTERN_H
#define PATTERN_H

#include <stdbool.h>
#include <stdint.h>

/**
 * struct and type to hold information on
 * how an LED channel/value changes over time
 *
 * Note: Every LED has three channels
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
