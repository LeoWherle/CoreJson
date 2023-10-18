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

    #define ARRSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

// typedef function pointer example
/** Lexer handle **/
typedef void (*json_lexer_func_t)(const char **json, token_t *token);
/** Parser handle **/
typedef int (*parse_func_t)(json_value_t *val, token_t *par, const char **jsn);
/** Printer handle **/
typedef void (*json_print_func_t)(
    json_value_t *val, uint32_t depth, bool format, int fd);


struct json_lexer_s {
    char charcter;
    json_lexer_func_t func_table;
};

struct json_object_s {
    json_value_t *values;
    char **keys;
    size_t size;
};

struct json_array_s {
    json_value_t *elements;
    size_t size;
};


/** HELPER **/
token_t *parse_string(const char **json, token_t *token);
token_t *parse_number(const char **json, token_t *token);

token_t *parse_char(const char **json, token_t *token, token_type_e type);
token_t *parse_string_spec(
    const char **json, token_t *token, token_type_e type, const char *str);


/** LEXER */
void jsn_token_end(const char **json, token_t *token);
void jsn_token_left_brace(const char **json, token_t *token);
void jsn_token_right_brace(const char **json, token_t *token);
void jsn_token_left_bracket(const char **json, token_t *token);
void jsn_token_right_bracket(const char **json, token_t *token);
void jsn_token_true(const char **json, token_t *token);
void jsn_token_false(const char **json, token_t *token);
void jsn_token_null(const char **json, token_t *token);
void jsn_token_colon(const char **json, token_t *token);
void jsn_token_comma(const char **json, token_t *token);
void jsn_token_string(const char **json, token_t *token);
void jsn_token_number(const char **json, token_t *token);


/** PARSER */
int jsn_tkn_parse_string(
    json_value_t *value, token_t *token, UNUSED const char **json);
int jsn_tkn_parse_number(
    json_value_t *value, token_t *token, UNUSED const char **json);
int jsn_tkn_parse_true(
    json_value_t *value, UNUSED token_t *token, UNUSED const char **json);
int jsn_tkn_parse_false(
    json_value_t *value, UNUSED token_t *token, UNUSED const char **json);
int jsn_tkn_parse_null(
    json_value_t *value, UNUSED token_t *token, UNUSED const char **json);
int jsn_tkn_parse_object(
    json_value_t *value, UNUSED token_t *token, const char **json);
int jsn_tkn_parse_array(
    json_value_t *value, UNUSED token_t *token, const char **json);


/** PRINTER **/
void jsn_object_print(
    json_value_t *value, uint32_t depth, bool format, int fd);
void jsn_array_print(
    json_value_t *value, uint32_t depth, bool format, int fd);
void jsn_number_print(
    json_value_t *value, uint32_t depth, bool format, int fd);
void jsn_bool_print(
    json_value_t *value, uint32_t depth, bool format, int fd);
void jsn_string_print(
    json_value_t *value, uint32_t depth, bool format, int fd);
void jsn_null_print(
    json_value_t *value, uint32_t depth, bool format, int fd);

void print_spaces(uint32_t depth, int fd, bool format);
void jsn_value_print(json_value_t *jsonValue, uint32_t, bool format, int fd);


/** FREE **/
void json_object_free(json_object_t *object);
void json_array_free(json_array_t *array);


/** MARVIN **/
    #define LEXER_VALUE_END '\0', jsn_token_end
    #define LEXER_VALUE_LEFT_BRACE '{', jsn_token_left_brace
    #define LEXER_VALUE_RIGHT_BRACE '}', jsn_token_right_brace
    #define LEXER_VALUE_LEFT_BRACKET '[', jsn_token_left_bracket
    #define LEXER_VALUE_RIGHT_BRACKET ']', jsn_token_right_bracket
    #define LEXER_VALUE_COLON ':', jsn_token_colon
    #define LEXER_VALUE_COMMA ',', jsn_token_comma
    #define LEXER_VALUE_TRUE 't', jsn_token_true
    #define LEXER_VALUE_FALSE 'f', jsn_token_false
    #define LEXER_VALUE_NULL 'n', jsn_token_null
    #define LEXER_VALUE_STRING '\"', jsn_token_string

#endif /* !COREJSON_INTERNAL_H_ */
