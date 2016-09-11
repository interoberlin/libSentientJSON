
#ifndef SENTIENT_JSON_H
#define SENTIENT_JSON_H

#include <stdint.h>

#include "callbacks.h"
#include "jsmn.h"

/**
 * Interprets Sentient JSON strings and
 * invokes the approriate callback functions
 */
void sentient_json_interpret(char*, callbacks_t*);

#endif
