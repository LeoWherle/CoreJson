#include "corejson_internal.h"
#include "builder/corejson_array.h"

#include <criterion/criterion.h>

Test(jsn_array_add, null)
{
    json_value_t *array = NULL;

    array = jsn_array_create();

    jsn_array_add_null(array);
    cr_assert_eq(array->array_value->size, 1);
    cr_assert_eq(array->array_value->elements[0].type, JSON_NULL);

    jsn_free(array);
}

Test(jsn_array_add, bool)
{
    json_value_t *array = NULL;

    array = jsn_array_create();

    if (jsn_array_add_bool(array, true)) {
        cr_assert_fail("jsn_array_add_bool failed");
        return;
    }
    cr_assert_eq(array->array_value->size, 1);
    cr_assert_eq(array->array_value->elements[0].type, JSON_BOOL);
    cr_assert_eq(array->array_value->elements[0].bool_value, true);

    jsn_free(array);
}

Test(jsn_array_add, number)
{
    json_value_t *array = NULL;

    array = jsn_array_create();

    if(jsn_array_add_number(array, 42)) {
        cr_assert_fail("jsn_array_add_number failed");
        return;
    }
    cr_assert_eq(array->array_value->size, 1);
    cr_assert_eq(array->array_value->elements[0].type, JSON_NUMBER);
    cr_assert_eq(array->array_value->elements[0].number_value, 42);

    jsn_free(array);
}

Test(jsn_array_add, string)
{
    json_value_t *array = NULL;

    array = jsn_array_create();

    jsn_array_add_string(array, "Hello World");
    cr_assert_eq(array->array_value->size, 1);
    cr_assert_eq(array->array_value->elements[0].type, JSON_STRING);
    cr_assert_str_eq(array->array_value->elements[0].string_value, "Hello World");

    jsn_free(array);
}

Test(jsn_array_add, object)
{
    json_value_t *array = NULL;
    json_object_t *object = NULL;

    array = jsn_array_create();
    object = malloc(sizeof(json_object_t));
    object->keys = NULL;
    object->values = NULL;
    object->size = 0;

    if (object == NULL) {
        cr_assert_fail("malloc failed");
        return;
    }
    jsn_array_add_object(array, object);
    cr_assert_eq(array->array_value->size, 1);
    cr_assert_eq(array->array_value->elements[0].type, JSON_OBJECT);
    cr_assert_eq(array->array_value->elements[0].object_value, object);

    jsn_free(array);
}

Test(jsn_array_add, array)
{
    json_value_t *array = NULL;
    json_array_t *array2 = NULL;

    array = jsn_array_create();
    array2 = malloc(sizeof(json_array_t));
    array2->elements = NULL;
    array2->size = 0;

    if (array2 == NULL) {
        cr_assert_fail("malloc failed");
        return;
    }
    jsn_array_add_array(array, array2);
    cr_assert_eq(array->array_value->size, 1);
    cr_assert_eq(array->array_value->elements[0].type, JSON_ARRAY);
    cr_assert_eq(array->array_value->elements[0].array_value, array2);

    jsn_free(array);
}

Test(jsn_object_add, boolean)
{
    json_value_t *object = NULL;

    object = jsn_object_create();

    jsn_object_add_bool(object, "bool", true);
    cr_assert_eq(object->object_value->size, 1);
    cr_assert_str_eq(object->object_value->keys[0], "bool");
    cr_assert_eq(object->object_value->values[0].type, JSON_BOOL);
    cr_assert_eq(object->object_value->values[0].bool_value, true);

    jsn_free(object);
}

Test(jsn_object_add, boolean_false)
{
    json_value_t *object = NULL;

    object = jsn_object_create();

    jsn_object_add_bool(object, "bool", false);
    cr_assert_eq(object->object_value->size, 1);
    cr_assert_str_eq(object->object_value->keys[0], "bool");
    cr_assert_eq(object->object_value->values[0].type, JSON_BOOL);
    cr_assert_eq(object->object_value->values[0].bool_value, false);

    jsn_free(object);
}

Test(jsn_object_add, number)
{
    json_value_t *object = NULL;

    object = jsn_object_create();

    jsn_object_add_number(object, "number", 42);
    cr_assert_eq(object->object_value->size, 1);
    cr_assert_str_eq(object->object_value->keys[0], "number");
    cr_assert_eq(object->object_value->values[0].type, JSON_NUMBER);
    cr_assert_eq(object->object_value->values[0].number_value, 42);

    jsn_free(object);
}

Test(jsn_object_add, string)
{
    json_value_t *object = NULL;

    object = jsn_object_create();

    jsn_object_add_string(object, "string", "Hello World");
    cr_assert_eq(object->object_value->size, 1);
    cr_assert_str_eq(object->object_value->keys[0], "string");
    cr_assert_eq(object->object_value->values[0].type, JSON_STRING);
    cr_assert_str_eq(object->object_value->values[0].string_value, "Hello World");

    jsn_free(object);
}

Test(jsn_object_add, object)
{
    json_value_t *object = NULL;
    json_object_t *object2 = NULL;

    object = jsn_object_create();
    object2 = malloc(sizeof(json_object_t));
    object2->keys = NULL;
    object2->values = NULL;
    object2->size = 0;

    if (object2 == NULL) {
        cr_assert_fail("malloc failed");
        return;
    }
    jsn_object_add_object(object, "object", object2);
    cr_assert_eq(object->object_value->size, 1);
    cr_assert_str_eq(object->object_value->keys[0], "object");
    cr_assert_eq(object->object_value->values[0].type, JSON_OBJECT);
    cr_assert_eq(object->object_value->values[0].object_value, object2);

    jsn_free(object);
}

Test(jsn_object_add, array)
{
    json_value_t *object = NULL;
    json_array_t *array = NULL;

    object = jsn_object_create();
    array = malloc(sizeof(json_array_t));    
    array->elements = NULL;
    array->size = 0;

    if (array == NULL) {
        cr_assert_fail("malloc failed");
        return;
    }
    jsn_object_add_array(object, "array", array);
    cr_assert_eq(object->object_value->size, 1);
    cr_assert_str_eq(object->object_value->keys[0], "array");
    cr_assert_eq(object->object_value->values[0].type, JSON_ARRAY);
    cr_assert_eq(object->object_value->values[0].array_value, array);

    jsn_free(object);
}
