/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** corejson_lexer
*/

#ifndef COREJSON_LEXER_H_
#define COREJSON_LEXER_H_

typedef enum {
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_ERROR,
    TOKEN_END,
} token_type_e;

#define IS_WHITESPACE(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r')
#define IS_NUMBER(c)     (isdigit(c) || c == '.' || c == '+' || c == '-')

typedef struct {
    token_type_e type;
#define VALUE_LEN_MAX 255
    char value[VALUE_LEN_MAX + 1];
} token_t;

token_t *next_token(const char **p, token_t *token);

const char *token_type_get_string(token_type_e type);

#endif /* !COREJSON_LEXER_H_ */
