/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** jsn_tkn_colon
*/

#include "corejson/lexer.h"

void jsn_token_colon(const char **json, token_t *token)
{
    parse_char(json, token, TOKEN_COLON);
}
