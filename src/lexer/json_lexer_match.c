/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_lexer
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corejson_internal.h"

static struct json_lexer_s lexer_table[] =
{
    {LEXER_VALUE_END},
    {LEXER_VALUE_STRING},
    {LEXER_VALUE_TRUE},
    {LEXER_VALUE_FALSE},
    {LEXER_VALUE_NULL},
    {LEXER_VALUE_LEFT_BRACE},
    {LEXER_VALUE_RIGHT_BRACE},
    {LEXER_VALUE_LEFT_BRACKET},
    {LEXER_VALUE_RIGHT_BRACKET},
    {LEXER_VALUE_COLON},
    {LEXER_VALUE_COMMA},
};

void skip_whitespace(const char **json)
{
    while (IS_WHITESPACE(**json)) {
        (*json)++;
    }
}

token_t *next_token(const char **json, token_t *token)
{
    uint32_t i = 0;

    token->value[0] = '\0';
    skip_whitespace(json);
    for (i = 0; i < ARRSIZE(lexer_table); i++) {
        if (lexer_table[i].charcter == **json) {
            lexer_table[i].func_table(json, token);
            break;
        }
    }
    if (i == ARRSIZE(lexer_table)) {
        jsn_token_number(json, token);
    }
    return token;
}
