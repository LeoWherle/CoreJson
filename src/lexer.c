#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corejson_lexer.h"

const char *token_tTypeString[] = {
    "String",
    "Number",
    "Boolean-true",
    "Boolean-false",
    "Null",
    "Brace-L",
    "Brace-R",
    "Bracket-L",
    "Bracket-R",
    "Colon",
    "Comma",
    "Error",
    "End",
};

// Structure to represent a token
#define IS_WHITESPACE(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r')
#define IS_NUMBER(c)     (isdigit(c) || c == '.' || c == '+' || c == '-')

// Function to skip whitespace characters
static void skip_whitespace(const char **json)
{
    while (IS_WHITESPACE(**json)) {
        (*json)++;
    }
}

static bool is_numeric(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    if (*str == '-' || *str == '+') {
        str++;
    }

    bool has_decimal = false;
    bool has_exponent = false;

    while (*str) {
        if (isdigit(*str)) {
            str++;
        } else if (*str == '.') {
            if (has_decimal || has_exponent) {
                return false;
            }
            has_decimal = true;
            str++;
        } else if (*str == 'e' || *str == 'E') {
            if (has_exponent) {
                return false;
            }
            str++;
            if (*str == '-' || *str == '+') {
                str++;
            }
            has_exponent = true;
        } else {
            return false;
        }
    }
    return true;
}

// Function to parse a string token
static token_t *parse_string(const char **json, token_t *token)
{
    token->type = TOKEN_STRING;
    token->value[0] = '\0';
    size_t str_len = 0;
    const char *start_pos = NULL;

    (*json)++;
    start_pos = *json;
    while (**json != '\0') {
        if (**json == '\"') {
            str_len = (size_t) ((*json) - start_pos);
            if (str_len > VALUE_MAX_LEN) {
                token->type = TOKEN_ERROR;
                return token;
            }
            memcpy(token->value, start_pos, str_len);
            token->value[str_len] = '\0';
            (*json)++;
            return token;
        }
        (*json)++;
    }
    token->type = TOKEN_ERROR;
    return token;
}

// Function to parse a number token
static token_t *parse_number(const char **json, token_t *token)
{
    token->type = TOKEN_NUMBER;
    token->value[0] = '\0';

    while (**json != '\0' && IS_NUMBER(**json)) {
        strncat(token->value, *json, 1);
        (*json)++;
    }
    return token;
}

// Function to identify and tokenize the next JSON token
token_t *next_token(const char **json, token_t *token)
{
    token->value[0] = '\0';

    skip_whitespace(json);

    switch (**json) {
        case '\0': token->type = TOKEN_END; break;
        case '{':
            token->type = TOKEN_LEFT_BRACE;
            strncat(token->value, *json, 1);
            (*json)++;
            break;
        case '}':
            token->type = TOKEN_RIGHT_BRACE;
            strncat(token->value, *json, 1);
            (*json)++;
            break;
        case '[':
            token->type = TOKEN_LEFT_BRACKET;
            strncat(token->value, *json, 1);
            (*json)++;
            break;
        case ']':
            token->type = TOKEN_RIGHT_BRACKET;
            strncat(token->value, *json, 1);
            (*json)++;
            break;
        case ':':
            token->type = TOKEN_COLON;
            strncat(token->value, *json, 1);
            (*json)++;
            break;
        case ',':
            token->type = TOKEN_COMMA;
            strncat(token->value, *json, 1);
            (*json)++;
            break;
        case 't':
            if (strncmp(*json, "true", 4) == 0) {
                token->type = TOKEN_TRUE;
                strcpy(token->value, "true");
                *json += 4;
            } else {
                token->type = TOKEN_ERROR;
            }
            break;
        case 'f':
            if (strncmp(*json, "false", 5) == 0) {
                token->type = TOKEN_FALSE;
                strcpy(token->value, "false");
                *json += 5;
            } else {
                token->type = TOKEN_ERROR;
            }
            break;
        case 'n':
            if (strncmp(*json, "null", 4) == 0) {
                token->type = TOKEN_NULL;
                strcpy(token->value, "null");
                *json += 4;
            } else {
                token->type = TOKEN_ERROR;
            }
            break;
        case '\"': token = parse_string(json, token); break;
        default:
            if (isdigit(**json) || **json == '-') {
                token = parse_number(json, token);
            } else {
                token->type = TOKEN_ERROR;
            }
            break;
    }
    // printf("%s\t%s\n", token_tTypeString[token->type],token->value);

    return token;
}
