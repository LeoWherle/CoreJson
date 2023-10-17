#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corejson_lexer.h"

static void skip_whitespace(const char **json)
{
    while (IS_WHITESPACE(**json)) {
        (*json)++;
    }
}

static token_t *_parse_string_data(
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

static token_t *parse_string(const char **json, token_t *token)
{
    const char *start_pos = NULL;

    token->type = TOKEN_STRING;
    token->value[0] = '\0';

    (*json)++;
    start_pos = *json;
    while (**json != '\0') {
        if (**json == '\"') {
            token = _parse_string_data(json, token, start_pos);
            return token;
        }
        (*json)++;
    }
    token->type = TOKEN_ERROR;
    return token;
}

static token_t *parse_number(const char **json, token_t *token)
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

static token_t *parse_char(const char **json, token_t *token, token_type_e type)
{
    token->type = type;
    *token->value = **json;
    *token->value = '\0';
    (*json)++;
    return token;
}

static token_t *parse_string_spec(
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

token_t *next_token(const char **json, token_t *token)
{
    token->value[0] = '\0';
    skip_whitespace(json);
    switch (**json) {
        case '\0': token->type = TOKEN_END; break;
        case '{': parse_char(json, token, TOKEN_LEFT_BRACE); break;
        case '}': parse_char(json, token, TOKEN_RIGHT_BRACE); break;
        case '[': parse_char(json, token, TOKEN_LEFT_BRACKET); break;
        case ']': parse_char(json, token, TOKEN_RIGHT_BRACKET); break;
        case ':': parse_char(json, token, TOKEN_COLON); break;
        case ',': parse_char(json, token, TOKEN_COMMA); break;
        case 't': parse_string_spec(json, token, TOKEN_TRUE, "true"); break;
        case 'f': parse_string_spec(json, token, TOKEN_FALSE, "false"); break;
        case 'n': parse_string_spec(json, token, TOKEN_NULL, "null"); break;
        case '\"': parse_string(json, token); break;
        default: parse_number(json, token); break;
    }
    return token;
}

