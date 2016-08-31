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
        //printf("The char at position %d is %x: '%c'\n", cursor, c, c);
        if (c == (uint8_t) '{')
        {
            level++;
            //printf("Descending to level %d\n", level);
        }
        else if (c == '}')
        {
            level--;
            //printf("Emerging to level %d%s\n", level, (level == 0) ? " (end of JSON reached)" : "");
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
void extract_bracket_contents(parser_t* parser, char** s)
{
    int begin = index_of_opening_bracket(*s);
    if (begin < 0)
    {
        parser->error_handler("Opening bracket ('{') not found");
        return;
    }
    printf("Opening bracket at string index %d\n", begin);

    int end   = index_of_closing_bracket(*s, begin);
    if (end < 0)
    {
        parser->error_handler("Closing bracket ('}') not found");
        return;
    }
    printf("Closing bracket at string index %d\n", end);

    // string shall end before closing bracket
    *((*s)+end) = 0;

    // new string shall begin with content after opening bracket
    *s = (*s)+begin+1;
}

/**
 * Remove spaces at beginning and end of string
 */
void trim_spaces(char** s)
{
    while (**s == ' ')
    {
        printf("%s\n", *s);
        (*s)++;
    }

    uint8_t length = strlen(*s);
    int cursor = length;
    while (cursor-- >= 0 && *((*s)+cursor) == ' ')
        **s = 0;
}

/**
 * Finds the first comman in string
 *
 * @return Index of first comma or -1 on error
 */
int find_comma(char* s)
{
    uint8_t cursor = 0;
    uint8_t length = strlen(s);

    // until end of string
    while (cursor < length)
    {
        // look for semicolon
        if (*(s+cursor) == ',')
            return cursor;
        cursor++;
    }

    return -1;
}

/**
 * Finds the first semicolon in string
 *
 * @return Index of first semicolon or -1 on error
 */
int find_semicolon(char* s)
{
    uint8_t cursor = 0;
    uint8_t length = strlen(s);

    // until end of string
    while (cursor < length)
    {
        // look for semicolon
        if (*(s+cursor) == ':')
            return cursor;
        cursor++;
    }

    return -1;
}

/**
 * Return string until first semicolon,
 * terminates string with null character
 * and increments original string pointer
 * to first character after semicolon
 *
 * @return Key as string
 */
char* until_semicolon(char** s, int index_semicolon)
{
    // save original string pointer
    char* result = *s;

    // terminate string here
    *((*s)+index_semicolon) = 0;

    // modify original string
    *s = (*s)+index_semicolon+1;

    return result;
}

/**
 * Processes the string after a semicolon (value of key-value pair),
 * terminates the value with null character
 * and updates original string pointer to first character after value
 *
 * @return Value as string
 */
char* after_semicolon(parser_t* parser, char** s)
{
    printf("After semicolon: %s\n", *s);

    // values must be in brackets
    extract_bracket_contents(parser, s);

    char* original = *s;

    // increment original string pointer
    *s = (*s)+strlen(*s)+1;

    return original;
}

/**
 * Main JSON parsing function
 */
void parse(parser_t* parser, char* data, uint8_t length)
{
    // disregard strings outside brackets
    printf("Original string is \"%s\"\n", data);
    extract_bracket_contents(parser, &data);
    printf("String trimmed to \"%s\"\n", data);

    // walk through bracket content
    int index_comma = 0;
    int index_semicolon = find_semicolon(data);

    while (index_semicolon > -1)
    {
        printf("String \"%s\"\n", data);
        printf("Semicolon at string index %d\n", index_semicolon);
        char* key   = until_semicolon(&data, index_semicolon);
        printf("Key: %s\n", key);
        char* value = after_semicolon(parser, &data);
        printf("Value: %s\n", value);

        printf("Remaining string: %s\n", data);
        index_comma     = find_comma(data);
        data += index_comma+1;
        index_semicolon = find_semicolon(data);
        printf("Comma at index %d, semicolon at index %d\n", index_comma, index_semicolon);
        if (index_comma == -1 || index_semicolon == -1 || index_comma > index_semicolon)
        {
            break;
        }
    }
}
