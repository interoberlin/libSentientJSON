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

/**
 * Search for the first opening bracket in string
 *
 * @return Index of bracket or -1 on error
 */
int index_of_opening_bracket(char* s)
{
    uint8_t cursor = 0;
    uint8_t length = strlen(s);

    while (cursor < length && *(s+cursor) != '{')
        cursor++;

    // opening bracket found?
    if (*(s+cursor) == '{')
        return cursor;
    return -1;
}

/**
 * Search for closing bracket,
 * corresponding to opening bracket at the given string index
 *
 * @return Index of closing bracket or -1 on error
 */
int index_of_closing_bracket(char* s, uint8_t index_opening_bracket)
{
    uint8_t level = 0;
    uint8_t cursor = index_opening_bracket;
    uint8_t length = strlen(s);

    while (cursor < length)
    {
        uint8_t c = *(s+cursor);
        printf("The char at position %d is %x: '%c'\n", cursor, c, c);
        if (c == (uint8_t) '{')
        {
            level++;
            printf("Descending to level %d\n", level);
        }
        else if (c == '}')
        {
            level--;
            printf("Emerging to level %d%s\n", level, (level == 0) ? " (end of JSON reached)" : "");
            if (level == 0)
                break;
        }

        cursor++;
    }

    return cursor;
}

/**
 * Trim parsed string
 * by returning JSON start (opening bracket)
 * and inserting null terminator at closing bracket
 */
void trim(parser_t* parser, char** s)
{
    uint8_t begin = index_of_opening_bracket(*s);
    if (begin < 0)
    {
        parser->error_handler("Opening bracket ('{') not found");
        return *s;
    }
    printf("JSON begins at string index %d\n", begin);

    uint8_t end   = index_of_closing_bracket(*s, begin);
    if (end < 0)
    {
        parser->error_handler("Closing bracket ('}') not found");
        return *s;
    }
    printf("JSON ends at string index %d\n", end);

    // string shall end with closing bracket
    *((*s)+end+1) = 0;

    // new string shall begin with opening bracket
    (*s) = (*s)+begin;
}

/**
 * Main JSON parsing function
 */
void parse(parser_t* parser, char* data, uint8_t length)
{
    printf("Original string is \"%s\"\n", data);
    trim(parser, &data);
    printf("String trimmed to \"%s\"\n", data);
}
