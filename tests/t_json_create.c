#include "corejson/internal.h"

#include <criterion/criterion.h>


Test(jsn_create, test_bool)
{
    json_value_t *value = jsn_bool_create(true);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_BOOL);
    cr_assert_eq(value->bool_value, true);
    jsn_free(value);
}

Test(jsn_create, test_number)
{
    json_value_t *value = jsn_number_create(42);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->number_value, 42);
    jsn_free(value);
}

Test(jsn_create, test_string)
{
    json_value_t *value = jsn_string_create("Hello World");

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_STRING);
    cr_assert_str_eq(value->string_value, "Hello World");
    jsn_free(value);
}

Test(jsn_create, test_array)
{
    json_value_t *value = jsn_array_create();

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_ARRAY);
    cr_assert_not_null(value->array_value);
    cr_assert_eq(value->array_value->size, 0);
    cr_assert_null(value->array_value->elements);
    jsn_free(value);
}

Test(jsn_create, test_object)
{
    json_value_t *value = jsn_object_create();

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_OBJECT);
    cr_assert_not_null(value->object_value);
    cr_assert_eq(value->object_value->size, 0);
    cr_assert_null(value->object_value->values);
    cr_assert_null(value->object_value->keys);
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
    cr_assert_eq(value->bool_value, false);
    jsn_free(value);
}

Test(jsn_create, test_number_big)
{
    json_value_t *value = jsn_number_create(35678901234567600);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->number_value, 35678901234567600.0);
    jsn_free(value);
}

Test(jsn_create, test_number_negative)
{
    json_value_t *value = jsn_number_create(-42);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->number_value, -42);
    jsn_free(value);
}

Test(jsn_create, test_number_float)
{
    json_value_t *value = jsn_number_create(42.42);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->number_value, 42.42);
    jsn_free(value);
}

Test(jsn_create, test_number_float_negative)
{
    json_value_t *value = jsn_number_create(-42.42);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->number_value, -42.42);
    jsn_free(value);
}

Test(jsn_create, test_string_empty)
{
    json_value_t *value = jsn_string_create("");

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_STRING);
    cr_assert_str_eq(value->string_value, "");
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
    cr_assert_not_null(value->array_value);
    cr_assert_eq(value->array_value->size, 0);
    cr_assert_null(value->array_value->elements);
    jsn_free(value);
}

Test(jsn_create, test_object_null)
{
    json_value_t *value = jsn_object_create();

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_OBJECT);
    cr_assert_not_null(value->object_value);
    cr_assert_eq(value->object_value->size, 0);
    cr_assert_null(value->object_value->values);
    cr_assert_null(value->object_value->keys);
    jsn_free(value);
}
