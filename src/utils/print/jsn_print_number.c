/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_parse_array
*/

#include <stdio.h>
#include "corejson/internal.h"

void jsn_number_print(json_value_t *jsonValue, UNUSED uint32_t depth,
    UNUSED uint32_t format, int fd)
{
    if (jsonValue->nbr_val == (int) jsonValue->nbr_val) {
        dprintf(fd, "%d", (int) jsonValue->nbr_val);
        return;
    } else if (jsonValue->nbr_val == (long) jsonValue->nbr_val) {
        dprintf(fd, "%ld", (long) jsonValue->nbr_val);
        return;
    } else {
        dprintf(fd, "%f", jsonValue->nbr_val);
        return;
    }
}
