/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** corejson_lexer_internal
*/

#ifndef COREJSON_INTERNAL_H_
#define COREJSON_INTERNAL_H_

#include "corejson.h"

#define UNUSED __attribute__((unused))

// typedef function pointer example

typedef int (*parse_func_t)(JSONValue *jns, token_t *parent, const char **json);

int jns_parse_string(JSONValue *jns, token_t *parent, const char **json);
int jns_parse_number(JSONValue *jns, token_t *parent, const char **json);
int jns_parse_true(JSONValue *jns, token_t *parent, const char **json);
int jns_parse_false(JSONValue *jns, token_t *parent, const char **json);
int jns_parse_null(JSONValue *jns, token_t *parent, const char **json);
int jns_parse_object(JSONValue *jns, token_t *parent, const char **json);
int jns_parse_array(JSONValue *jns, token_t *parent, const char **json);

#endif /* !COREJSON_INTERNAL_H_ */
