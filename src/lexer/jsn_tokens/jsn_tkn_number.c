/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** jsn_tkn_comma
*/

#include "corejson/lexer.h"

void jsn_token_number(const char **json, token_t *token)
{
    parse_number(json, token);
}
