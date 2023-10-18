/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** corejson
*/

#ifndef COREJSON_H_
// clang-format off
    #define COREJSON_H_

    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>

    #ifndef UNUSED
        #define UNUSED __attribute__((unused))
    #endif

    #ifndef ARRSIZE
        #define ARRSIZE(arr) (sizeof(arr) / sizeof(arr[0]))
    #endif

    #define NULL_STR "null"
    #define TRUE_STR "true"
    #define FALSE_STR "false"
    #define VALUE_LEN_MAX 255
// clang-format on

typedef struct json_value_s json_value_t;
typedef struct json_object_s json_object_t;
typedef struct json_array_s json_array_t;

typedef enum {
    JSON_STRING,
    JSON_NUMBER,
    JSON_TRUE,
    JSON_FALSE,
    JSON_NULL,
    JSON_OBJECT,
    JSON_ARRAY
} json_value_type;

// clang-format off
    #define IS_JSON_VALUE(t) (t >= JSON_STRING && t <= JSON_ARRAY)
// clang-format on

struct json_value_s {
    json_value_type type;
    union {
        char string_value[VALUE_LEN_MAX + 1];
        double number_value;
        json_object_t *object_value;
        json_array_t *array_value;
        int bool_value;
    };
};

/********************************* PARSING ***********************************/
/**
 * @brief Parse a json string
 *
 * @param json The json string to parse (must be a json object)
 * @return A graph in json_value_t or NULL if an error occured
 */
json_value_t *jsn_parse(const char *json);

/**
 * @note only use this function if you know what you are doing
 * @brief Parse a json string
 *
 * @param json The json string to parse (must be a json value type)
 * @return A graph in json_value_t or NULL if an error occured
 */
json_value_t *jsn_parse_value(const char **json);

/**
 * @note only use this function if you know what you are doing
 * @brief Parse a json object and set the value in jsonValue
 *
 * @param json The json string to parse (must be a json value type)
 * @param jsonValue The json value to set the json_object_t in
 * @return A graph in json_value_t or NULL if an error occured
 */
json_value_t *jsn_parse_object(const char **json, json_value_t *jsonValue);

/**
 * @note only use this function if you know what you are doing
 * @brief Parse a json array and set the value in jsonValue
 *
 * @param json The json string to parse (must be a json value type)
 * @param jsonValue The json value to set the json_array_t in
 * @return A graph in json_value_t or NULL if an error occured
 */
json_value_t *jsn_parse_array(const char **json, json_value_t *jsonValue);

/**************************** CONSTRUCTORS ***********************************/

/**
 * @brief Add key/value pair to json object
 *
 * @param object the json object to add the key/value pair to
 * @param value the json value to add to the json object
 * @param key the key to add to the json object
 * @return 0 if success, 1 otherwise (allocation error)
 */
int jsn_object_data_add(
    json_object_t *object, json_value_t *value, const char *key);

/**
 * @brief Add element to json array
 *
 * @param array the json array to add the element to
 * @param element the json value to add to the json array
 * @return 0 if success, 1 otherwise (allocation error)
 */
int jsn_array_data_add(json_array_t *array, json_value_t *element);

/****************************** PRINT ****************************************/

/**
 * @brief Print a json value to file descriptor (fd) with indentation (format)
 * @note Only prints json objects and json arrays (and their children), the
 * parent json value must be a json object or a json array
 *
 * @param json the json value to print
 * @param format if 0 don't format, if format > 0 format using (format * 2) as
 * the number of spaces to indent
 * @param fd the file descriptor to print to (can be STDOUT_FILENO)
 */
void jsn_print(json_value_t *json, uint32_t format, int fd);

/***************************** DESTRUCTORS ***********************************/

/**
 * @brief Free a json value, including its children
 *
 * @param jsonValue the json value to free
 */
void jsn_free(json_value_t *jsonValue);

/**
 * @brief Free a json object's childrens
 *
 * @param object the json object to free the childrens of
 */
void jsn_value_free(json_value_t *jsonValue);

#endif /* !COREJSON_H_ */
