
#include "sentient_json.h"

/**
 * Parse a Sentient JSON string using Jasmine JSON parser,
 * extract all specified key functionalities and
 * call the appropriate callback functions
 */
void sentient_json_interpret(char* json, callbacks_t* callbacks)
{
	jsmn_parser p;
	jsmntok_t token[NUM_TOKENS];

	jsmn_init(&p);
	int count = jsmn_parse(&p, json, strlen(json), token, NUM_TOKENS);
	if (count < 0)
	{
		callbacks->error("Jasmine failed.");
		return;
	}

    // iterate over top-level tokens
    for (int i=0; i < count; i++)
    {
        if (jsmn_equals(json, &token[i], "leds"))
        {
            callbacks->debug("leds!\n");
        }
    }
}
