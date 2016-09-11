
#include "callbacks.h"

/**
 * Assign callbacks to callback container
 */
void set_callbacks(
        callbacks_t* callbacks,
        set_led_callback_t set_led,
        set_led_channel_callback_t set_led_channel,
        error_callback_t error,
        debug_callback_t debug
        )
{
    callbacks->set_led = set_led;
    callbacks->set_led_channel = set_led_channel;
    callbacks->error = error;
    callbacks->debug = debug;
}
