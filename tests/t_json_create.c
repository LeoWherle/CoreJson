#include "corejson/internal.h"

#include <criterion/criterion.h>


Test(jsn_create, test_bool)
{
    json_value_t *value = jsn_bool_create(true);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_BOOL);
    cr_assert_eq(value->bool_val, true);
    jsn_free(value);
}

Test(jsn_create, test_number)
{
    json_value_t *value = jsn_number_create(42);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->nbr_val, 42);
    jsn_free(value);
}

Test(jsn_create, test_string)
{
    json_value_t *value = jsn_string_create("Hello World");

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_STRING);
    cr_assert_str_eq(value->str_val, "Hello World");
    jsn_free(value);
}

Test(jsn_create, test_array)
{
    json_value_t *value = jsn_array_create();

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_ARRAY);
    cr_assert_not_null(value->arr_val);
    cr_assert_eq(value->arr_val->size, 0);
    cr_assert_null(value->arr_val->elem);
    jsn_free(value);
}

Test(jsn_create, test_object)
{
    json_value_t *value = jsn_object_create();

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_OBJECT);
    cr_assert_not_null(value->obj_val);
    cr_assert_eq(value->obj_val->size, 0);
    cr_assert_null(value->obj_val->values);
    cr_assert_null(value->obj_val->keys);
    jsn_free(value);
}

Test(jsn_create, test_null)
{
    json_value_t *value = jsn_null_create();

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_NULL);
    jsn_free(value);
}

Test(jsn_create, test_bool_false)
{
    json_value_t *value = jsn_bool_create(false);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_BOOL);
    cr_assert_eq(value->bool_val, false);
    jsn_free(value);
}

Test(jsn_create, test_number_big)
{
    json_value_t *value = jsn_number_create(35678901234567600);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->nbr_val, 35678901234567600.0);
    jsn_free(value);
}

Test(jsn_create, test_number_negative)
{
    json_value_t *value = jsn_number_create(-42);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->nbr_val, -42);
    jsn_free(value);
}

Test(jsn_create, test_number_float)
{
    json_value_t *value = jsn_number_create(42.42);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->nbr_val, 42.42);
    jsn_free(value);
}

Test(jsn_create, test_number_float_negative)
{
    json_value_t *value = jsn_number_create(-42.42);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->nbr_val, -42.42);
    jsn_free(value);
}

Test(jsn_create, test_string_empty)
{
    json_value_t *value = jsn_string_create("");

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_STRING);
    cr_assert_str_eq(value->str_val, "");
    jsn_free(value);
}

Test(jsn_create, test_string_null)
{
    json_value_t *value = jsn_string_create(NULL);

    cr_assert_null(value);
    jsn_free(value);
}

Test(jsn_create, test_array_null)
{
    json_value_t *value = jsn_array_create();

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_ARRAY);
    cr_assert_not_null(value->arr_val);
    cr_assert_eq(value->arr_val->size, 0);
    cr_assert_null(value->arr_val->elem);
    jsn_free(value);
}

Test(jsn_create, test_object_null)
{
    json_value_t *value = jsn_object_create();

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_OBJECT);
    cr_assert_not_null(value->obj_val);
    cr_assert_eq(value->obj_val->size, 0);
    cr_assert_null(value->obj_val->values);
    cr_assert_null(value->obj_val->keys);
    jsn_free(value);
}
