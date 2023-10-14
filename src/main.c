#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// token_t types
typedef enum {
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_ERROR,
    TOKEN_END,
} token_type_e;

const char *token_tTypeString[] = {
    "String",
    "Number",
    "Boolean-true",
    "Boolean-false",
    "Null",
    "Brace-L",
    "Brace-R",
    "Bracket-L",
    "Bracket-R",
    "Colon",
    "Comma",
    "Error",
    "End",
};

// Structure to represent a token
typedef struct {
    token_type_e type;
#define VALUE_MAX_LEN 255
    char value[VALUE_MAX_LEN + 1];
} token_t;

#define IS_WHITESPACE(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r')
#define IS_NUMBER(c)     (isdigit(c) || c == '.' || c == '+' || c == '-')

// Function to skip whitespace characters
static void skip_whitespace(const char **json)
{
    while (IS_WHITESPACE(**json)) {
        (*json)++;
    }
}

static bool is_numeric(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    if (*str == '-' || *str == '+') {
        str++;
    }

    bool has_decimal = false;
    bool has_exponent = false;

    while (*str) {
        if (isdigit(*str)) {
            str++;
        } else if (*str == '.') {
            if (has_decimal || has_exponent) {
                return false;
            }
            has_decimal = true;
            str++;
        } else if (*str == 'e' || *str == 'E') {
            if (has_exponent) {
                return false;
            }
            str++;
            if (*str == '-' || *str == '+') {
                str++;
            }
            has_exponent = true;
        } else {
            return false;
        }
    }
    return true;
}

// Function to parse a string token
static token_t parse_string(const char **json)
{
    token_t token;
    token.type = TOKEN_STRING;
    token.value[0] = '\0';
    size_t str_len = 0;
    const char *start_pos = NULL;

    (*json)++;
    start_pos = *json;
    while (**json != '\0') {
        if (**json == '\"') {
            str_len = (size_t) ((*json) - start_pos);
            if (str_len > VALUE_MAX_LEN) {
                token.type = TOKEN_ERROR;
                return token;
            }
            memcpy(token.value, start_pos, str_len);
            token.value[str_len] = '\0';
            (*json)++;
            return token;
        }
        (*json)++;
    }
    token.type = TOKEN_ERROR;
    return token;
}

// Function to parse a number token
static token_t parse_number(const char **json)
{
    token_t token;
    token.type = TOKEN_NUMBER;
    token.value[0] = '\0';

    while (**json != '\0' && IS_NUMBER(**json)) {
        strncat(token.value, *json, 1);
        (*json)++;
    }

    return token;
}

// Function to identify and tokenize the next JSON token
static token_t next_token(const char **json)
{
    token_t token;
    token.value[0] = '\0';

    skip_whitespace(json);

    switch (**json) {
        case '\0': token.type = TOKEN_END; break;
        case '{':
            token.type = TOKEN_LEFT_BRACE;
            strncat(token.value, *json, 1);
            (*json)++;
            break;
        case '}':
            token.type = TOKEN_RIGHT_BRACE;
            strncat(token.value, *json, 1);
            (*json)++;
            break;
        case '[':
            token.type = TOKEN_LEFT_BRACKET;
            strncat(token.value, *json, 1);
            (*json)++;
            break;
        case ']':
            token.type = TOKEN_RIGHT_BRACKET;
            strncat(token.value, *json, 1);
            (*json)++;
            break;
        case ':':
            token.type = TOKEN_COLON;
            strncat(token.value, *json, 1);
            (*json)++;
            break;
        case ',':
            token.type = TOKEN_COMMA;
            strncat(token.value, *json, 1);
            (*json)++;
            break;
        case 't':
            if (strncmp(*json, "true", 4) == 0) {
                token.type = TOKEN_TRUE;
                strcpy(token.value, "true");
                *json += 4;
            } else {
                token.type = TOKEN_ERROR;
            }
            break;
        case 'f':
            if (strncmp(*json, "false", 5) == 0) {
                token.type = TOKEN_FALSE;
                strcpy(token.value, "false");
                *json += 5;
            } else {
                token.type = TOKEN_ERROR;
            }
            break;
        case 'n':
            if (strncmp(*json, "null", 4) == 0) {
                token.type = TOKEN_NULL;
                strcpy(token.value, "null");
                *json += 4;
            } else {
                token.type = TOKEN_ERROR;
            }
            break;
        case '\"': token = parse_string(json); break;
        default:
            if (isdigit(**json) || **json == '-') {
                token = parse_number(json);
            } else {
                token.type = TOKEN_ERROR;
            }
            break;
    }

    return token;
}

// Example usage of the lexer
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct JSONValue JSONValue;
typedef struct JSONObject JSONObject;
typedef struct JSONArray JSONArray;

// JSON value types
typedef enum {
    JSON_STRING,
    JSON_NUMBER,
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_TRUE,
    JSON_FALSE,
    JSON_NULL
} JSONValueType;

// JSON value structure
struct JSONValue {
    JSONValueType type;
    union {
        char string_value[VALUE_MAX_LEN + 1];
        double number_value;
        JSONObject *object_value;
        JSONArray *array_value;
        bool bool_value;
    };
};

// JSON object structure
struct JSONObject {
    JSONValue *properties;
    char **keys;
    size_t size;
};

// JSON array structure
struct JSONArray {
    JSONValue *elements;
    size_t size;
};

// Function to parse a JSON object
JSONValue *parse_object(const char **json);

// Function to parse a JSON array
JSONValue *parse_array(const char **json);

// Function to parse JSON values
JSONValue *parse_value(const char **json)
{
    token_t token = next_token(json);
    JSONValue *value = NULL;

    value = malloc(sizeof(JSONValue));
    if (value == NULL) {
        return NULL;
    }
    switch (token.type) {
        case TOKEN_STRING:
            value->type = JSON_STRING;
            strncpy(
                value->string_value, token.value, sizeof(value->string_value));
            break;
        case TOKEN_NUMBER:
            value->type = JSON_NUMBER;
            value->number_value = atof(token.value);
            break;
        case TOKEN_TRUE:
            value->type = JSON_TRUE;
            value->bool_value = true;
            break;
        case TOKEN_FALSE:
            value->type = JSON_FALSE;
            value->bool_value = false;
            break;
        case TOKEN_NULL: value->type = JSON_NULL; break;
        case TOKEN_LEFT_BRACE:
            free(value);
            value = parse_object(json);
            break;
        case TOKEN_LEFT_BRACKET:
            free(value);
            value = parse_array(json);
            break;
        default:
            free(value);
            value = NULL;
            break;
    }
    return value;
}

// Function to parse a JSON object
JSONValue *parse_object(const char **json)
{
    char key[VALUE_MAX_LEN] = {0};
    JSONValue *value = NULL;
    JSONObject *object = NULL;
    JSONValue *property = NULL;

    value = malloc(sizeof(JSONValue));
    object = malloc(sizeof(JSONObject));
    if (value == NULL || object == NULL) {
        free(value);
        free(object);
    }
    object->size = 0;
    object->properties = NULL;
    object->keys = NULL;
    value->type = JSON_OBJECT;

    while (true) {
        token_t token = next_token(json);
        if (token.type == TOKEN_RIGHT_BRACE)
            break; // End of object

        if (token.type != TOKEN_STRING) {
            value->type = JSON_NULL; // Error in parsing
            break;
        }

        strncpy(key, token.value, sizeof(key));

        token = next_token(json);
        if (token.type != TOKEN_COLON) {
            value->type = JSON_NULL; // Error in parsing
            break;
        }

        property = parse_value(json);
        if (property == NULL) {
            value->type = JSON_NULL;
            break;
        }

        // Expand the object's properties array
        object->properties =
            realloc(object->properties, (object->size + 1) * sizeof(JSONValue));
        if (object->properties == NULL) {
            value->type = JSON_NULL;
            free(property);
            break;
        }
        object->keys =
            realloc(object->keys, (object->size + 1) * sizeof(char *));
        if (object->keys == NULL) {
            value->type = JSON_NULL;
            free(property);
            break;
        }
        memcpy(&object->properties[object->size], property, sizeof(JSONValue));
        free(property);
        object->keys[object->size] = strdup(key);
        object->size++;

        // Check for more properties or end of object
        token = next_token(json);
        if (token.type == TOKEN_COMMA) {
            continue;
        } else if (token.type == TOKEN_RIGHT_BRACE) {
            break;
        } else {
            value->type = JSON_NULL; // Error in parsing
            break;
        }
    }

    if (value->type != JSON_NULL) {
        value->object_value = object;
    } else {
        // Clean up on error
        for (size_t i = 0; i < object->size; i++) {
            free(object->keys[i]);
        }
        free(object->keys);
        free(object->properties);
    }
    return value;
}

// Function to parse a JSON array
JSONValue *parse_array(const char **json)
{
    JSONValue *value = NULL;
    JSONArray *array = NULL;
    JSONValue *element = NULL;

    value = malloc(sizeof(JSONValue));
    array = malloc(sizeof(JSONArray));
    if (value == NULL || array == NULL) {
        free(value);
        free(array);
        return NULL;
    }

    array->size = 0;
    array->elements = NULL;
    value->type = JSON_ARRAY;
    while (true) {
        token_t token = next_token(json);
        if (token.type == TOKEN_RIGHT_BRACKET)
            break; // End of array

        element = parse_value(json);
        if (element == NULL) {
            value->type = JSON_NULL;
            break;
        }

        // Expand the array's elements array
        array->elements =
            realloc(array->elements, (array->size + 1) * sizeof(JSONValue));
        if (array->elements == NULL) {
            value->type = JSON_NULL;
            free(element);
            break;
        }
        memcpy(element, &array->elements[array->size], sizeof(JSONValue));
        free(element);
        array->size++;

        // Check for more elements or end of array
        token = next_token(json);
        if (token.type == TOKEN_COMMA) {
            continue;
        } else if (token.type == TOKEN_RIGHT_BRACKET) {
            break;
        } else {
            value->type = JSON_NULL; // Error in parsing
            break;
        }
    }

    if (value->type != JSON_NULL) {
        value->array_value = array;
    } else {
        // Clean up on error
        for (size_t i = 0; i < array->size; i++) {
            if (array->elements[i].type == JSON_STRING) {
                free(array->elements[i].string_value);
            }
        }
        free(array->elements);
    }

    return value;
}

// Main JSON parsing function
JSONValue *parse_json(const char *json)
{
    return parse_value(&json);
}

// Function to recursively free JSON data
void free_json(JSONValue *jsonValue)
{
    if (jsonValue->type == JSON_OBJECT) {
        for (size_t i = 0; i < jsonValue->object_value->size; i++) {
            free_json(&jsonValue->object_value->properties[i]);
            free(jsonValue->object_value->keys[i]);
        }
        free(jsonValue->object_value->keys);
        free(jsonValue->object_value->properties);
    } else if (jsonValue->type == JSON_ARRAY) {
        for (size_t i = 0; i < jsonValue->array_value->size; i++) {
            free_json(&jsonValue->array_value->elements[i]);
        }
        free(jsonValue->array_value->elements);
    }
    free(jsonValue);
}

void print_spaces(uint32_t depth)
{
    for (uint32_t i = 0; i < depth; i++) {
        printf("  ");
    }
}

void print_json(JSONValue *jsonValue, uint32_t depth)
{
    switch (jsonValue->type) {
        case JSON_ARRAY:
            printf("[\n");
            for (uint32_t i = 0; i < jsonValue->array_value->size; i++) {
                print_spaces(depth + 1);
                print_json(&jsonValue->array_value->elements[i], depth + 1);
            }
            printf("]\n");
            break;
        case JSON_OBJECT:
            print_spaces(depth);
            printf("{\n");
            for (uint32_t i = 0; i < jsonValue->object_value->size; i++) {
                print_spaces(depth + 1);
                printf("\"%s\": ", jsonValue->object_value->keys[i]);
                print_json(&jsonValue->object_value->properties[i], depth + 1);
            }
            print_spaces(depth);
            printf("}\n");
            break;
        case JSON_NUMBER: printf("%e\n", jsonValue->number_value); break;
        case JSON_FALSE:
        case JSON_TRUE:
            printf("%s\n", jsonValue->bool_value ? "true" : "false");
            break;
        case JSON_STRING: printf("%s\n", jsonValue->string_value); break;
        case JSON_NULL: printf("null"); break;

        default: break;
    }
}
void json_free(JSONValue *jsonValue)
{
    switch (jsonValue->type) {
        case JSON_ARRAY:
            for (uint32_t i = 0; i < jsonValue->array_value->size; i++) {
                json_free(&jsonValue->array_value->elements[i]);
            }
            free(jsonValue->array_value->elements);
            free(jsonValue->array_value);
            break;
        case JSON_OBJECT:
            for (uint32_t i = 0; i < jsonValue->object_value->size; i++) {
                json_free(&jsonValue->object_value->properties[i]);
                free(jsonValue->object_value->keys[i]);
            }
            free(jsonValue->object_value->properties);
            free(jsonValue->object_value->keys);
            free(jsonValue->object_value);
            break;
        case JSON_NUMBER:
        case JSON_FALSE:
        case JSON_TRUE:
        case JSON_STRING:
        case JSON_NULL: break;

        default: break;
    }
}

// Example usage
int main()
{
    const char *json_str2 =
        "{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}";
    const char *json_str = "{\"name\":\"John\",\"age\":[30, 12, 33],\"city\":\"New York\"}";

    JSONValue *json = parse_value(&json_str);

    printf("start\n");
    if (json->type != JSON_OBJECT) {
        printf("Error: Invalid JSON\n");
        return 1;
    }

    // Accessing JSON data
    for (size_t i = 0; i < json->object_value->size; i++) {
        printf("Key: %s, Value: ", json->object_value->keys[i]);
        if (json->object_value->properties[i].type == JSON_STRING) {
            printf("\"%s\"\n", json->object_value->properties[i].string_value);
        } else if (json->object_value->properties[i].type == JSON_NUMBER) {
            printf("%lf\n", json->object_value->properties[i].number_value);
        }
    }

    print_json(json, 0);

    // Free allocated memory
    json_free(json);
    free(json);
    return 0;
}
