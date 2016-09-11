/**
 * This is a simple program to test JSON parsing
 * for the Sentient Light project
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "callbacks.h"
#include "sentient_json.h"

#define DEBUG_INTERPRETER

/*
 * Stub callback functions
 */
void set_led(uint32_t led, uint32_t value)
{
    printf("Setting LED %d to value %d...\n", led, value);
}

void set_led_channel(uint32_t led, uint32_t value, uint32_t bitmask)
{
    printf("Setting LED %d to value %d using bitmask %d...\n", led, value, bitmask);
}

void error_handler(char* message)
{
    printf("Error: %s\n", message);
}


int main()
{
    printf("Begin JSON parser test...\n");

    /*
     * Note:
     *   char* json = "...";
     * is not valid here,
     * because string literals are
     * by default not writeable in C.
     */
    char test_json[] = "{ \"leds\" : [{\"index\": 1, \"values\": [0,0,0]}, {\"index\": \"2\", \"values\": [255,255,255]} ]}";

    // define parser callback functions
    callbacks_t c;
    callbacks_t* callbacks = &c;
    set_callbacks(callbacks, &set_led, &set_led_channel, &error_handler);

    // parse test JSON
    sentient_json_interpret(test_json, callbacks);

    printf("JSON parser test completed.\n");
    return 0;
}
