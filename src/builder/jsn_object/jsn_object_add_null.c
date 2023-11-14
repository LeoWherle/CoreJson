/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_create_advanced
*/

#include <stdlib.h>
#include <string.h>
#include "corejson/builder.h"
#include "corejson/internal.h"

json_error_t jsn_object_add_null(
    json_value_t *value, const char *key)
{
    return jsn_object_add_number(value, key, 0);
}
