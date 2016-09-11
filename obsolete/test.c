/**
 * This is a simple program to test JSON parsing
 * for the Sentient Light project
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "pattern.h"
#include "json.h"

#define DEBUG_PARSER

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

    // Notation char* json = "{}"; is invalid here!
    // String literals are not writeable
    char json[] = "  { 0: {1,2,3}, 1 : {20,30,40}  }  ";

    parser_t parser;

    set_parser_callbacks(&parser, &set_led, &set_led_channel, &error_handler);
    process_json(&parser, json, strlen(json));

    printf("JSON parser test completed.\n");
    return 0;
}
