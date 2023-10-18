/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** corejson_lexer
*/

#ifndef COREJSON_LEXER_H_
// clang-format off
    #define COREJSON_LEXER_H_

    #include "corejson.h"
    #include "logs.h"
// clang-format on

typedef enum {
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    /*OBJECT*/
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    /*ARRAY*/
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_ERROR,
    TOKEN_END
} token_type_e;

// clang-format off
    #define IS_WHITESPACE(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r')
    #define IS_NUMBER(c)     (isdigit(c) || c == '.' || c == '+' || c == '-')

    #define IS_TOKN_BOOL(t) (t == TOKEN_TRUE || t == TOKEN_FALSE)
    #define IS_TOKN_INT(t)  (t == TOKEN_NUMBER || IS_TOKN_BOOL(t))
    #define IS_TOKN_NULLABLE(t) (t == TOKEN_NULL || t == TOKEN_STRING)
    #define IS_TOKN_ATOMIC(tk) (IS_TOKN_INT(tk) || IS_TOKN_NULLABLE(tk))
    /** IS Container **/
    #define IS_TOKN_CONTR(t) (t == TOKEN_LEFT_BRACE || t == TOKEN_LEFT_BRACKET)
    #define IS_TOKN_VAL(token) (IS_TOKN_ATOMIC(token) || IS_TOKN_CONTR(token))
// clang-format on

typedef struct {
    token_type_e type;
    char value[VALUE_LEN_MAX + 1];
} token_t;

/** Lexer handle **/
typedef void (*json_lexer_func_t)(const char **json, token_t *token);
/** Parser handle **/
typedef int (*parse_func_t)(json_value_t *val, token_t *par, const char **jsn);

struct json_lexer_s {
    char charcter;
    json_lexer_func_t func_table;
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

token_t *next_token(const char **p, token_t *token);

const char *token_type_get_string(token_type_e type);

/** MARVIN **/
// clang-format off
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
// clang-format on

#endif /* !COREJSON_LEXER_H_ */
