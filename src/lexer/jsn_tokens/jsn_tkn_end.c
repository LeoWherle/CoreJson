/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** jsn_tkn_end
*/

#include "corejson_internal.h"

void jsn_token_end(UNUSED const char **json, token_t *token)
{
    token->type = TOKEN_END;
}
