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
#include "corejson_lexer.h"

static token_t *parse_string_data(
    const char **json, token_t *token, const char *start_pos)
{
    size_t str_len = 0;

    str_len = (size_t) ((*json) - start_pos);
    if (str_len > VALUE_LEN_MAX) {
        token->type = TOKEN_ERROR;
        return token;
    }
    memcpy(token->value, start_pos, str_len);
    token->value[str_len] = '\0';
    (*json)++;
    return token;
}

token_t *parse_string(const char **json, token_t *token)
{
    const char *start_pos = NULL;

    token->type = TOKEN_STRING;
    token->value[0] = '\0';
    (*json)++;
    start_pos = *json;
    while (**json != '\0') {
        if (**json == '\"') {
            token = parse_string_data(json, token, start_pos);
            return token;
        }
        (*json)++;
    }
    token->type = TOKEN_ERROR;
    return token;
}

token_t *parse_number(const char **json, token_t *token)
{
    uint32_t i = 0;

    if (isdigit(**json) || **json == '-') {
        token->type = TOKEN_NUMBER;
        *((double *) (token->value)) = 0;
        while (**json != '\0' && IS_NUMBER(**json)) {
            token->value[i] = **json;
            (*json)++;
            i++;
        }
        *(token->value + i + 1) = '\0';
    } else {
        token->type = TOKEN_ERROR;
    }
    return token;
}

token_t *parse_char(const char **json, token_t *token, token_type_e type)
{
    token->type = type;
    *token->value = **json;
    *token->value = '\0';
    (*json)++;
    return token;
}

token_t *parse_string_spec(
    const char **json, token_t *token, token_type_e type, const char *str)
{
    size_t str_len = strlen(str);

    if (strncmp(*json, str, str_len) == 0) {
        token->type = type;
        memcpy(token->value, str, str_len + 1);
        *json += str_len;
    } else {
        token->type = TOKEN_ERROR;
    }
    return token;
}
