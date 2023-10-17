/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** corejson_lexer
*/

#ifndef COREJSON_LEXER_H_
    #define COREJSON_LEXER_H_

    #include "logs.h"

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

    #define IS_WHITESPACE(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r')
    #define IS_NUMBER(c)     (isdigit(c) || c == '.' || c == '+' || c == '-')

    #define IS_TOKN_BOOL(t) (t == TOKEN_TRUE || t == TOKEN_FALSE)
    #define IS_TOKN_INT(t)  (t == TOKEN_NUMBER || IS_TOKN_BOOL(t))
    #define IS_TOKN_NULLABLE(t) (t == TOKEN_NULL || t == TOKEN_STRING)
    #define IS_TOKN_ATOMIC(tk) (IS_TOKN_INT(tk) || IS_TOKN_NULLABLE(tk))
    /** IS Container **/
    #define IS_TOKN_CONTR(t) (t == TOKEN_LEFT_BRACE || t == TOKEN_LEFT_BRACKET)
    #define IS_TOKN_VAL(token) (IS_TOKN_ATOMIC(token) || IS_TOKN_CONTR(token))

    #define VALUE_LEN_MAX 255
typedef struct {
    token_type_e type;
    char value[VALUE_LEN_MAX + 1];
} token_t;

token_t *next_token(const char **p, token_t *token);

const char *token_type_get_string(token_type_e type);

#endif /* !COREJSON_LEXER_H_ */
