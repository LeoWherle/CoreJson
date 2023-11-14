/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** main
*/

#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "corejson.h"
#include "corejson/version.h"
#include "corejson/builder.h"

static int read_file(int fd, char **json_str)
{
    int json_str_len = 0;
    char buffer[4096] = {0};
    ssize_t read_len = 0;

    read_len = read(fd, buffer, 4096);
    while (read_len > 0) {
        json_str_len += (int) read_len;
        *json_str =
            reallocarray(*json_str, (size_t) json_str_len + 1, sizeof(char));
        if (*json_str == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory\n");
            return -1;
        }
        memcpy(
            &(*json_str)[json_str_len - read_len], buffer, (size_t) read_len);
        (*json_str)[json_str_len] = '\0';
        read_len = read(fd, buffer, 4096);
    }
    return json_str_len;
}

int read_json_file(const char *filename, char **json_str)
{
    int fd = open(filename, O_RDONLY);
    int json_str_len = 0;

    if (fd == -1) {
        printf("Error: File does not exist\n");
        return 1;
    }
    json_str_len = read_file(fd, json_str);
    close(fd);
    if (json_str_len == -1) {
        return 1;
    } else if (json_str_len == 0) {
        dprintf(STDERR_FILENO, "Error: File is empty\n");
        return 1;
    }
    return 0;
}

int print_json(const char *json_str, uint32_t format, int fd)
{
    json_value_t *json = NULL;

    json = jsn_parse(json_str);
    if (json == NULL) {
        fprintf(stderr, "Error: Failed to parse JSON\n");
        return 1;
    } else if (json->type != JSON_OBJECT && json->type != JSON_ARRAY) {
        fprintf(stderr, "Error: Invalid JSON\n");
        jsn_free(json);
        return 1;
    }
    jsn_print(json, format, fd);
    jsn_free(json);
    return 0;
}

int print_version(void)
{
    printf("CoreJson\n");
    printf("    version : %s\n", VERSION_GIT);
    printf("    date    : %s\n", VERSION_DATE);
    return 0;
}

// int main(int argc, char *argv[])
// {
//     int ret = 0;
//     char *json_str = NULL;

//     if (argc != 2) {
//         printf("Usage: %s <file>\n", argv[0]);
//         return 1;
//     }
//     if (strcmp(argv[1], "-v") == 0) {
//         return print_version();
//     }
//     if (read_json_file(argv[1], &json_str) != 0) {
//         return 1;
//     }
//     ret = print_json(json_str, JSN_FORMAT_4_SPACES, STDOUT_FILENO);
//     free(json_str);
//     return ret;
// }

int main(int argc, char *argv[])
{
    json_value_t *object = NULL;
    json_value_t *array = NULL;
    double array_val[] = {12, 23, 3};

    object = jsn_object_create();
    if (object == NULL) {
        return 1;
    }
    array = jsn_array_create_from_list_number(array_val, 3);
    if (array == NULL) {
        return 1;
    }

    if (jsn_object_add_array(object, "array", array->arr_val) == JSN_ERROR) {
        return 1;
    }

    jsn_print(object, JSN_FORMAT_4_SPACES, STDOUT_FILENO);

    jsn_free(object);
    return 0;
}