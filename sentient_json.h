
#ifndef SENTIENT_JSON_H
#define SENTIENT_JSON_H

#include <stdint.h>
#include <string.h>

#include "callbacks.h"
#include "jsmn.h"

// maximum number of tokens per JSON
#define NUM_TOKENS 128

/**
 * Interprets Sentient JSON strings and
 * invokes the approriate callback functions
 */
void sentient_json_interpret(char*, callbacks_t*);

#endif
