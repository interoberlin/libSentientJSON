
#include "callbacks.h"

/**
 * Assign callbacks to callback container
 */
void set_callbacks(
        callbacks_t* parser,
        set_led_callback_t set_led,
        set_led_channel_callback_t set_led_channel,
        error_callback_t error_handler
        )
{
    parser->set_led = set_led;
    parser->set_led_channel = set_led_channel;
    parser->error_handler = error_handler;
}
