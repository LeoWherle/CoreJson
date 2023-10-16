#include <criterion/criterion.h>
#include "corejson.h"

Test(json_parser, test_parse_number)
{
    const char *json = "123.45";
    JSONValue *value = json_parse(json);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->number_value, 123.45);
    json_free(value);
}

Test(json_parser, test_parse_string)
{
    const char *json = "\"hello, world!\"";
    JSONValue *value = json_parse(json);
    cr_assert_eq(value->type, JSON_STRING);
    cr_assert_str_eq(value->string_value, "hello, world!");
    json_free(value);
}

Test(json_parser, test_parse_true)
{
    const char *json = "true";
    JSONValue *value = json_parse(json);
    cr_assert_eq(value->type, JSON_TRUE);
    json_free(value);
}

Test(json_parser, test_parse_false)
{
    const char *json = "false";
    JSONValue *value = json_parse(json);
    cr_assert_eq(value->type, JSON_FALSE);
    json_free(value);
}

Test(json_parser, test_parse_null)
{
    const char *json = "null";
    JSONValue *value = json_parse(json);
    cr_assert_eq(value->type, JSON_NULL);
    json_free(value);
}

Test(json_parser, test_parse_object)
{
    const char *json =
        "{\"name\": \"John\", \"age\": 30, \"city\": \"New York\"}";
    JSONValue *jjson = json_parse(json);
    cr_assert_eq(jjson->type, JSON_OBJECT);
    cr_assert_eq(jjson->object_value->size, 3);
    cr_assert_str_eq(jjson->object_value->keys[0], "name");
    cr_assert_eq(jjson->object_value->values[0].type, JSON_STRING);
    cr_assert_str_eq(jjson->object_value->values[0].string_value, "John");
    cr_assert_str_eq(jjson->object_value->keys[1], "age");
    cr_assert_eq(jjson->object_value->values[1].type, JSON_NUMBER);
    cr_assert_eq(jjson->object_value->values[1].number_value, 30);
    cr_assert_str_eq(jjson->object_value->keys[2], "city");
    cr_assert_eq(jjson->object_value->values[2].type, JSON_STRING);
    cr_assert_str_eq(jjson->object_value->values[2].string_value, "New York");
    json_free(jjson);
}

Test(json_parser, test_parse_array)
{
    const char *json = "[1, 2, 3]";
    JSONValue *jjson = json_parse(json);
    cr_assert_eq(jjson->type, JSON_ARRAY);
    cr_assert_eq(jjson->array_value->size, 3);
    cr_assert_eq(jjson->array_value->elements[0].type, JSON_NUMBER);
    cr_assert_eq(jjson->array_value->elements[0].number_value, 1);
    cr_assert_eq(jjson->array_value->elements[1].type, JSON_NUMBER);
    cr_assert_eq(jjson->array_value->elements[1].number_value, 2);
    cr_assert_eq(jjson->array_value->elements[2].type, JSON_NUMBER);
    cr_assert_eq(jjson->array_value->elements[2].number_value, 3);
    json_free(jjson);
}

Test(json_parser, test_parse_nested_array) {
    const char *json = "[1, [2, [3, 4], 5], 6]";
    JSONValue *value = json_parse(json);
    cr_assert_eq(value->type, JSON_ARRAY);
    cr_assert_eq(value->array_value->size, 3);

    cr_assert_eq(value->array_value->elements[0].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[0].number_value, 1);

    cr_assert_eq(value->array_value->elements[1].type, JSON_ARRAY);
    cr_assert_eq(value->array_value->elements[1].array_value->size, 3);

    cr_assert_eq(value->array_value->elements[1].array_value->elements[0].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[1].array_value->elements[0].number_value, 2);

    cr_assert_eq(value->array_value->elements[1].array_value->elements[1].type, JSON_ARRAY);
    cr_assert_eq(value->array_value->elements[1].array_value->elements[1].array_value->size, 2);

    cr_assert_eq(value->array_value->elements[1].array_value->elements[1].array_value->elements[0].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[1].array_value->elements[1].array_value->elements[0].number_value, 3);

    cr_assert_eq(value->array_value->elements[1].array_value->elements[1].array_value->elements[1].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[1].array_value->elements[1].array_value->elements[1].number_value, 4);

    cr_assert_eq(value->array_value->elements[1].array_value->elements[2].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[1].array_value->elements[2].number_value, 5);

    cr_assert_eq(value->array_value->elements[2].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[2].number_value, 6);
    json_free(value);
}