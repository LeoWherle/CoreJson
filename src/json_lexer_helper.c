#include <stdint.h>
#include "corejson_lexer.h"

const char *token_type_string[] = {
    "TOKEN_STRING",
    "TOKEN_NUMBER",
    "TOKEN_TRUE",
    "TOKEN_FALSE",
    "TOKEN_NULL",
    "TOKEN_LEFT_BRACE",
    "TOKEN_RIGHT_BRACE",
    "TOKEN_LEFT_BRACKET",
    "TOKEN_RIGHT_BRACKET",
    "TOKEN_COLON",
    "TOKEN_COMMA",
    "TOKEN_ERROR",
    "TOKEN_END",
};


const char *token_type_get_string(token_type_e type)
{
    return token_type_string[type];
}
