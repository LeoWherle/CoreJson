/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** json_print
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "corejson.h"

static void print_spaces(uint32_t depth, int fd)
{
    for (uint32_t i = 0; i < depth; i++) {
        dprintf(fd, "  ");
    }
}

static void json_array_print(
    json_array_t *array, uint32_t depth, bool format, int fd)
{
    dprintf(fd, "[");
    if (format) {
        dprintf(fd, "\n");
    }
    for (uint32_t i = 0; i < array->size; i++) {
        if (format) {
            print_spaces(depth + 1, fd);
        }
        json_print_value(&array->elements[i], depth + 1, format, fd);
        if (i < array->size - 1) {
            dprintf(fd, ",");
        }
        if (format) {
            dprintf(fd, "\n");
        }
    }
    if (format) {
        print_spaces(depth, fd);
    }
    dprintf(fd, "]");
}

static void json_object_print(
    json_object_t *object, uint32_t depth, bool format, int fd)
{
    dprintf(fd, "{");
    if (format) {
        dprintf(fd, "\n");
    }
    for (uint32_t i = 0; i < object->size; i++) {
        if (format) {
            print_spaces(depth + 1, fd);
        }
        dprintf(fd, "\"%s\": ", object->keys[i]);
        json_print_value(&object->values[i], depth + 1, format, fd);
        if (i < object->size - 1) {
            dprintf(fd, ",");
        }
        if (format) {
            dprintf(fd, "\n");
        }
    }
    dprintf(fd, "}");
}

static void json_number_print(json_value_t *jsonValue, int fd)
{
    // check if number is an integer
    if (jsonValue->number_value == (int) jsonValue->number_value) {
        dprintf(fd, "%d", (int) jsonValue->number_value);
        return;
    } else if (jsonValue->number_value == (long) jsonValue->number_value) {
        dprintf(fd, "%ld", (long) jsonValue->number_value);
        return;
    } else {
        dprintf(fd, "%f", jsonValue->number_value);
        return;
    }
}

void json_print_value(json_value_t *jsonValue, uint32_t depth, bool format, int fd)
{
    switch (jsonValue->type) {
        case JSON_ARRAY:
            json_array_print(jsonValue->array_value, depth, format, fd);
            break;
        case JSON_OBJECT:
            json_object_print(jsonValue->object_value, depth, format, fd);
            break;
        case JSON_NUMBER: json_number_print(jsonValue, fd); break;
        case JSON_FALSE:
        case JSON_TRUE:
            dprintf(fd, "%s", jsonValue->bool_value ? "true" : "false");
            break;
        case JSON_STRING: dprintf(fd, "\"%s\"", jsonValue->string_value); break;
        case JSON_NULL: dprintf(fd, "null"); break;

        default: break;
    }
}

void json_print(json_value_t *jsonValue, bool format, int fd)
{
    json_print_value(jsonValue, 0, format, fd);
}
