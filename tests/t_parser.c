#include <criterion/criterion.h>
#include "corejson/internal.h"

Test(json_parser, test_parse_number)
{
    const char *json = "123.45";
    json_value_t *value = jsn_parse_value(&json);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->nbr_val, 123.45);
    jsn_free(value);
}

Test(json_parser, test_parse_string)
{
    const char *json = "\"hello, world!\"";
    json_value_t *value = jsn_parse_value(&json);
    cr_assert_eq(value->type, JSON_STRING);
    cr_assert_str_eq(value->str_val, "hello, world!");
    jsn_free(value);
}

Test(json_parser, test_parse_true)
{
    const char *json = "true";
    json_value_t *value = jsn_parse_value(&json);
    cr_assert_eq(value->type, JSON_BOOL);
    jsn_free(value);
}

Test(json_parser, test_parse_false)
{
    const char *json = "false";
    json_value_t *value = jsn_parse_value(&json);
    cr_assert_eq(value->type, JSON_BOOL);
    jsn_free(value);
}

Test(json_parser, test_parse_null)
{
    const char *json = "null";
    json_value_t *value = jsn_parse_value(&json);
    cr_assert_eq(value->type, JSON_NULL);
    jsn_free(value);
}

Test(json_parser, test_parse_object)
{
    const char *json =
        "{\"name\": \"John\", \"age\": 30, \"city\": \"New York\"}";
    json_value_t *jjson = jsn_parse(json);
    cr_assert_eq(jjson->type, JSON_OBJECT);
    cr_assert_eq(jjson->obj_val->size, 3);
    cr_assert_str_eq(jjson->obj_val->keys[0], "name");
    cr_assert_eq(jjson->obj_val->values[0].type, JSON_STRING);
    cr_assert_str_eq(jjson->obj_val->values[0].str_val, "John");
    cr_assert_str_eq(jjson->obj_val->keys[1], "age");
    cr_assert_eq(jjson->obj_val->values[1].type, JSON_NUMBER);
    cr_assert_eq(jjson->obj_val->values[1].nbr_val, 30);
    cr_assert_str_eq(jjson->obj_val->keys[2], "city");
    cr_assert_eq(jjson->obj_val->values[2].type, JSON_STRING);
    cr_assert_str_eq(jjson->obj_val->values[2].str_val, "New York");
    jsn_free(jjson);
}

Test(json_parser, test_parse_array)
{
    const char *json = "[1, 2, 3]";
    json_value_t *jjson = jsn_parse_value(&json);
    cr_assert_eq(jjson->type, JSON_ARRAY);
    cr_assert_eq(jjson->arr_val->size, 3);
    cr_assert_eq(jjson->arr_val->elem[0].type, JSON_NUMBER);
    cr_assert_eq(jjson->arr_val->elem[0].nbr_val, 1);
    cr_assert_eq(jjson->arr_val->elem[1].type, JSON_NUMBER);
    cr_assert_eq(jjson->arr_val->elem[1].nbr_val, 2);
    cr_assert_eq(jjson->arr_val->elem[2].type, JSON_NUMBER);
    cr_assert_eq(jjson->arr_val->elem[2].nbr_val, 3);
    jsn_free(jjson);
}

Test(json_parser, test_parse_nested_array) {
    const char *json = "[1, [2, [3, 4], 5], 6]";
    json_value_t *value = jsn_parse_value(&json);
    cr_assert_eq(value->type, JSON_ARRAY);
    cr_assert_eq(value->arr_val->size, 3);

    cr_assert_eq(value->arr_val->elem[0].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[0].nbr_val, 1);

    cr_assert_eq(value->arr_val->elem[1].type, JSON_ARRAY);
    cr_assert_eq(value->arr_val->elem[1].arr_val->size, 3);

    cr_assert_eq(value->arr_val->elem[1].arr_val->elem[0].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[1].arr_val->elem[0].nbr_val, 2);

    cr_assert_eq(value->arr_val->elem[1].arr_val->elem[1].type, JSON_ARRAY);
    cr_assert_eq(value->arr_val->elem[1].arr_val->elem[1].arr_val->size, 2);

    cr_assert_eq(value->arr_val->elem[1].arr_val->elem[1].arr_val->elem[0].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[1].arr_val->elem[1].arr_val->elem[0].nbr_val, 3);

    cr_assert_eq(value->arr_val->elem[1].arr_val->elem[1].arr_val->elem[1].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[1].arr_val->elem[1].arr_val->elem[1].nbr_val, 4);

    cr_assert_eq(value->arr_val->elem[1].arr_val->elem[2].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[1].arr_val->elem[2].nbr_val, 5);

    cr_assert_eq(value->arr_val->elem[2].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[2].nbr_val, 6);
    jsn_free(value);
}