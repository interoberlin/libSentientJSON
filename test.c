/**
 * This is a simple program to test JSON parsing
 * for the Sentient Light project
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "pattern.h"
#include "json.h"

/*
 * Stub callback functions
 */
void set_led(uint8_t led, uint8_t value)
{
    printf("Setting LED\n");
}

void set_led_channel(uint8_t led, uint8_t value, uint8_t bitmask)
{
    printf("Setting LED channel\n");
}

void error_handler(char* message)
{
    printf("Error: %s\n", message);
}


int main()
{
    printf("Begin JSON parser test...\n");
    char* json = "  {}";
    parser_t parser;

    set_parser_callbacks(&parser, &set_led, &set_led_channel, &error_handler);
    parse(&parser, json, strlen(json));

    printf("JSON parser test completed.\n");
    return 0;
}
