/**
 * Declares how JSON parser callbacks should look like
 */

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <stdint.h>

/**
 * These types declares, how the callback function should look like,
 * that is executed by the parser in order to set the intensity of an LED or LED channel
 */
typedef void (*set_led_callback_t)(uint32_t led, uint32_t value);

// new_value = (old_value & bitmask) | value;
typedef void (*set_led_channel_callback_t)(uint32_t led, uint32_t value, uint32_t bitmask);

/**
 * Declares a callback, which is invoked in case of parsing errors
 */
typedef void (*error_callback_t)(char* message);

/**
 * A container for callbacks
 */
struct callbacks_s
{
    set_led_callback_t set_led;
    set_led_channel_callback_t set_led_channel;
    error_callback_t error_handler;
};
typedef struct callbacks_s callbacks_t;

/**
 * This function fills a callback container with pointers to callback functions
 */
void set_callbacks(
        callbacks_t*,
        set_led_callback_t,
        set_led_channel_callback_t,
        error_callback_t
        );

#endif
