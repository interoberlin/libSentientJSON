/**
 * This file implements a JSON parser
 * for strings incoming on the Interoberlin Sentient Light UART BLE service
 */

#include "json.h"

/**
 * Assign parser callbacks
 */
void set_parser_callbacks(
        parser_t* parser,
        set_led_callback_t set_led,
        set_led_channel_callback_t set_led_channel,
        error_callback_t error_handler
        )
{
    parser->set_led = set_led;
    parser->set_led_channel = set_led_channel;
    parser->error_handler = error_handler;
}

#define LEVEL_STRIP     0
#define LEVEL_LED       1
#define LEVEL_VALUE     2

/**
 * Main JSON parsing function
 */
void parse(parser_t* parser, char* data, uint8_t length)
{
    uint8_t cursor = 0;

    while (cursor < length && *(data+cursor) != '{')
        cursor++;

    if (*(data+cursor) != '{')
    {
        parser->error_handler("Invalid JSON: Must begin with '{'.");
        return;
    }
}
