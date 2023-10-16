
#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "corejson.h"
#include "version.h"

ssize_t read_file(int fd, char **json_str)
{
    ssize_t json_str_len = 0;
    char buf[BUFSIZ] = {0};
    ssize_t bytes_read = 0;

    bytes_read = read(fd, buf, sizeof(buf));
    if (bytes_read == -1) {
        perror("read");
        return -1;
    }
    while (bytes_read > 0) {
        json_str_len += bytes_read;
        *json_str = realloc(*json_str, json_str_len + 1);
        if (*json_str == NULL) {
            perror("realloc");
            return -1;
        }
        memcpy(*json_str + json_str_len - bytes_read, buf, bytes_read);
        (*json_str)[json_str_len] = '\0';
        bytes_read = read(fd, buf, sizeof(buf));
        if (bytes_read == -1) {
            perror("read");
            return -1;
        }
    }
    return json_str_len;
}

int parse_and_print_file(const char *file, bool format, int fd)
{
    int fd_file = -1;
    char *json_str_o = NULL;
    char *json_str = NULL;
    size_t json_str_len = 0;

    fd_file = open(file, O_RDONLY);
    if (fd_file == -1) {
        perror("open");
        return 1;
    }

    json_str_len = read_file(fd_file, &json_str_o);
    close(fd_file);
    if (json_str_len == 0) {
        dprintf(STDERR_FILENO, "Error: File is empty\n");
        return 1;
    }
    json_str = json_str_o;

    JSONValue *json = json_parse(json_str);
    if (json->type != JSON_OBJECT && json->type != JSON_ARRAY) {
        printf("Error: Invalid JSON\n");
        return 1;
    }
    json_print(json, format, fd);

    json_free(json);
    free(json_str_o);
    return 0;
}

int main(int arc, char *argv[])
{
    if (arc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-v") == 0) {
        printf("corejson\n");
        printf("    version : %s\n", VERSION_GIT);
        printf("    date    : %s\n", VERSION_DATE);
        return 0;
    }

    if (access(argv[1], F_OK) == -1) {
        printf("Error: File does not exist\n");
        return 1;
    }
    if (parse_and_print_file(argv[1], true, STDOUT_FILENO)) {
        return 1;
    }
    return 0;
}
