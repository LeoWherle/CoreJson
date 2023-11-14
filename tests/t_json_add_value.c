#include "corejson/internal.h"
#include "corejson/builder.h"

#include <criterion/criterion.h>

Test(jsn_array_add, null)
{
    json_value_t *array = NULL;

    array = jsn_array_create();

    jsn_array_add_null(array);
    cr_assert_eq(array->arr_val->size, 1);
    cr_assert_eq(array->arr_val->elem[0].type, JSON_NULL);

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
    cr_assert_eq(array->arr_val->size, 1);
    cr_assert_eq(array->arr_val->elem[0].type, JSON_BOOL);
    cr_assert_eq(array->arr_val->elem[0].bool_val, true);

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
    cr_assert_eq(array->arr_val->size, 1);
    cr_assert_eq(array->arr_val->elem[0].type, JSON_NUMBER);
    cr_assert_eq(array->arr_val->elem[0].nbr_val, 42);

    jsn_free(array);
}

Test(jsn_array_add, string)
{
    json_value_t *array = NULL;

    array = jsn_array_create();

    jsn_array_add_string(array, "Hello World");
    cr_assert_eq(array->arr_val->size, 1);
    cr_assert_eq(array->arr_val->elem[0].type, JSON_STRING);
    cr_assert_str_eq(array->arr_val->elem[0].str_val, "Hello World");

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
    cr_assert_eq(array->arr_val->size, 1);
    cr_assert_eq(array->arr_val->elem[0].type, JSON_OBJECT);
    cr_assert_eq(array->arr_val->elem[0].obj_val, object);

    jsn_free(array);
}

Test(jsn_array_add, array)
{
    json_value_t *array = NULL;
    json_array_t *array2 = NULL;

    array = jsn_array_create();
    array2 = malloc(sizeof(json_array_t));
    array2->elem = NULL;
    array2->size = 0;

    if (array2 == NULL) {
        cr_assert_fail("malloc failed");
        return;
    }
    jsn_array_add_array(array, array2);
    cr_assert_eq(array->arr_val->size, 1);
    cr_assert_eq(array->arr_val->elem[0].type, JSON_ARRAY);
    cr_assert_eq(array->arr_val->elem[0].arr_val, array2);

    jsn_free(array);
}

Test(jsn_object_add, boolean)
{
    json_value_t *object = NULL;

    object = jsn_object_create();

    jsn_object_add_bool(object, "bool", true);
    cr_assert_eq(object->obj_val->size, 1);
    cr_assert_str_eq(object->obj_val->keys[0], "bool");
    cr_assert_eq(object->obj_val->values[0].type, JSON_BOOL);
    cr_assert_eq(object->obj_val->values[0].bool_val, true);

    jsn_free(object);
}

Test(jsn_object_add, boolean_false)
{
    json_value_t *object = NULL;

    object = jsn_object_create();

    jsn_object_add_bool(object, "bool", false);
    cr_assert_eq(object->obj_val->size, 1);
    cr_assert_str_eq(object->obj_val->keys[0], "bool");
    cr_assert_eq(object->obj_val->values[0].type, JSON_BOOL);
    cr_assert_eq(object->obj_val->values[0].bool_val, false);

    jsn_free(object);
}

Test(jsn_object_add, number)
{
    json_value_t *object = NULL;

    object = jsn_object_create();

    jsn_object_add_number(object, "number", 42);
    cr_assert_eq(object->obj_val->size, 1);
    cr_assert_str_eq(object->obj_val->keys[0], "number");
    cr_assert_eq(object->obj_val->values[0].type, JSON_NUMBER);
    cr_assert_eq(object->obj_val->values[0].nbr_val, 42);

    jsn_free(object);
}

Test(jsn_object_add, string)
{
    json_value_t *object = NULL;

    object = jsn_object_create();

    jsn_object_add_string(object, "string", "Hello World");
    cr_assert_eq(object->obj_val->size, 1);
    cr_assert_str_eq(object->obj_val->keys[0], "string");
    cr_assert_eq(object->obj_val->values[0].type, JSON_STRING);
    cr_assert_str_eq(object->obj_val->values[0].str_val, "Hello World");

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
    cr_assert_eq(object->obj_val->size, 1);
    cr_assert_str_eq(object->obj_val->keys[0], "object");
    cr_assert_eq(object->obj_val->values[0].type, JSON_OBJECT);
    cr_assert_eq(object->obj_val->values[0].obj_val, object2);

    jsn_free(object);
}

Test(jsn_object_add, array)
{
    json_value_t *object = NULL;
    json_value_t *array = NULL;
    double array_val[] = {12, 23, 3};

    object = jsn_object_create();
    if (object == NULL) {
        cr_assert_fail("malloc failed");
        return;
    }
    array = jsn_array_create_from_list_number(array_val, 3);
    if (array == NULL) {
        cr_assert_fail("malloc failed");
        return;
    }
    cr_assert_eq(array->type, JSON_ARRAY);
    cr_assert_eq(array->arr_val->size, 3);
    cr_assert_eq(array->arr_val->elem[0].type, JSON_NUMBER);
    cr_assert_eq(array->arr_val->elem[0].nbr_val, 12);
    cr_assert_eq(array->arr_val->elem[1].type, JSON_NUMBER);
    cr_assert_eq(array->arr_val->elem[1].nbr_val, 23);
    cr_assert_eq(array->arr_val->elem[2].type, JSON_NUMBER);
    cr_assert_eq(array->arr_val->elem[2].nbr_val, 3);


    if(jsn_object_add_array(object, "array", array->arr_val) == JSN_ERROR) {
        cr_assert_fail("jsn_object_add_array failed");
        return;
    }
    cr_assert_eq(object->obj_val->size, 1);
    cr_assert_str_eq(object->obj_val->keys[0], "array");
    cr_assert_eq(object->obj_val->values[0].type, JSON_ARRAY);
    cr_assert_eq(object->obj_val->values[0].arr_val->size, 3);
    cr_assert_not(object->obj_val->values[0].arr_val->elem == NULL);
    cr_assert_eq(object->obj_val->values[0].arr_val->elem[0].type, JSON_NUMBER);
    cr_assert_eq(object->obj_val->values[0].arr_val->elem[0].nbr_val, 12);
    cr_assert_eq(object->obj_val->values[0].arr_val->elem[1].type, JSON_NUMBER);
    cr_assert_eq(object->obj_val->values[0].arr_val->elem[1].nbr_val, 23);
    cr_assert_eq(object->obj_val->values[0].arr_val->elem[2].type, JSON_NUMBER);
    cr_assert_eq(object->obj_val->values[0].arr_val->elem[2].nbr_val, 3);

    jsn_free(object);
}
