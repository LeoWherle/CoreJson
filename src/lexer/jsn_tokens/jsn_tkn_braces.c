/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** jsn_tkn_comma
*/

#include "corejson/lexer.h"

void jsn_token_left_brace(const char **json, token_t *token)
{
    parse_char(json, token, TOKEN_LEFT_BRACE);
}

void jsn_token_right_brace(const char **json, token_t *token)
{
    parse_char(json, token, TOKEN_RIGHT_BRACE);
}
