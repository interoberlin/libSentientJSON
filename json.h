/**
 * This file declares the parser for incoming JSON strings
 * and functions to attach the required handlers
 */

#ifndef JSON_H
#define JSON_H

#include <stdint.h>

/**
 * These types declares, how the callback function should look like,
 * that is executed by the parser in order to set the intensity of an LED or LED channel
 */
typedef void (*set_led_callback_t)(uint8_t led, uint8_t value);

// new_value = (old_value & bitmask) | value;
typedef void (*set_led_channel_callback_t)(uint8_t led, uint8_t value, uint8_t bitmask);

/**
 * A parser object
 */
struct parser_s
{
    set_led_callback_t set_led;
    set_led_channel_callback_t set_led_channel;
};
typedef struct parser_s parser_t;

/**
 * This function sets the callbacks for the parser in question
 */
void set_parser_callbacks(parser_t*, set_led_callback_t, set_led_channel_callback_t);

/**
 * Parsing happens here
 */
void parse(char* data, uint8_t length);

#endif
