#include "corejson/internal.h"
#include "corejson/builder.h"

#include <criterion/criterion.h>

Test(jsn_array_create_from_list, null)
{
    json_value_t *value = jsn_array_create_from_list_number(NULL, 0);
    cr_assert_null(value);
    value = jsn_array_create_from_list_string(NULL, 0);
    cr_assert_null(value);
    value = jsn_array_create_from_list_bool(NULL, 0);
    cr_assert_null(value);
    value = jsn_array_create_from_list_object(NULL, 0);
    cr_assert_null(value);
    value = jsn_array_create_from_list_array(NULL, 0);
    cr_assert_null(value);
}

Test(jsn_array_create_from_list, string)
{
    const char *list[] = {"Hello", "World", "!", NULL};
    json_value_t *value = jsn_array_create_from_list_string(list, 3);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_ARRAY);
    cr_assert_not_null(value->arr_val);
    cr_assert_eq(value->arr_val->size, 3);
    cr_assert_not_null(value->arr_val->elem);
    cr_assert_eq(value->arr_val->elem[0].type, JSON_STRING);
    cr_assert_str_eq(value->arr_val->elem[0].str_val, "Hello");
    cr_assert_eq(value->arr_val->elem[1].type, JSON_STRING);
    cr_assert_str_eq(value->arr_val->elem[1].str_val, "World");
    cr_assert_eq(value->arr_val->elem[2].type, JSON_STRING);
    cr_assert_str_eq(value->arr_val->elem[2].str_val, "!");
    jsn_free(value);
}


Test(jsn_array_create_from_list, number)
{
    double list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    json_value_t *value = jsn_array_create_from_list_number(list, 9);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_ARRAY);
    cr_assert_not_null(value->arr_val);
    cr_assert_eq(value->arr_val->size, 9);
    cr_assert_not_null(value->arr_val->elem);
    cr_assert_eq(value->arr_val->elem[0].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[0].nbr_val, 1);
    cr_assert_eq(value->arr_val->elem[1].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[1].nbr_val, 2);
    cr_assert_eq(value->arr_val->elem[2].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[2].nbr_val, 3);
    cr_assert_eq(value->arr_val->elem[3].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[3].nbr_val, 4);
    cr_assert_eq(value->arr_val->elem[4].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[4].nbr_val, 5);
    cr_assert_eq(value->arr_val->elem[5].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[5].nbr_val, 6);
    cr_assert_eq(value->arr_val->elem[6].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[6].nbr_val, 7);
    cr_assert_eq(value->arr_val->elem[7].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[7].nbr_val, 8);
    cr_assert_eq(value->arr_val->elem[8].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[8].nbr_val, 9);
    jsn_free(value);
}

Test(jsn_array_create_from_list, boolean)
{
    bool list[] = {true, false, true, false, true, false, true, false, true};
    json_value_t *value = jsn_array_create_from_list_bool(list, 9);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_ARRAY);
    cr_assert_not_null(value->arr_val);
    cr_assert_eq(value->arr_val->size, 9);
    cr_assert_not_null(value->arr_val->elem);
    cr_assert_eq(value->arr_val->elem[0].type, JSON_BOOL);
    cr_assert_eq(value->arr_val->elem[0].bool_val, true);
    cr_assert_eq(value->arr_val->elem[1].type, JSON_BOOL);
    cr_assert_eq(value->arr_val->elem[1].bool_val, false);
    cr_assert_eq(value->arr_val->elem[2].type, JSON_BOOL);
    cr_assert_eq(value->arr_val->elem[2].bool_val, true);
    cr_assert_eq(value->arr_val->elem[3].type, JSON_BOOL);
    cr_assert_eq(value->arr_val->elem[3].bool_val, false);
    cr_assert_eq(value->arr_val->elem[4].type, JSON_BOOL);
    cr_assert_eq(value->arr_val->elem[4].bool_val, true);
    cr_assert_eq(value->arr_val->elem[5].type, JSON_BOOL);
    cr_assert_eq(value->arr_val->elem[5].bool_val, false);
    cr_assert_eq(value->arr_val->elem[6].type, JSON_BOOL);
    cr_assert_eq(value->arr_val->elem[6].bool_val, true);
    cr_assert_eq(value->arr_val->elem[7].type, JSON_BOOL);
    cr_assert_eq(value->arr_val->elem[7].bool_val, false);
    cr_assert_eq(value->arr_val->elem[8].type, JSON_BOOL);
    cr_assert_eq(value->arr_val->elem[8].bool_val, true);
    jsn_free(value);
}


Test(jsn_array_create_from_list, object)
{
    json_value_t *object1 = NULL;
    json_value_t *object2 = NULL;
    json_value_t *object3 = NULL;

    object1 = jsn_object_create();
    object2 = jsn_object_create();
    object3 = jsn_object_create();
    if (object1 == NULL || object2 == NULL || object3 == NULL) {
        cr_assert_fail("Failed to create object");
    }
    if (jsn_object_add_string(object1, "name", "John")) {
        cr_assert_fail("Failed to add string to object");
    }
    if (jsn_object_add_number(object1, "age", 30)) {
        cr_assert_fail("Failed to add number to object");
    }
    if (jsn_object_add_string(object1, "city", "New York")) {
        cr_assert_fail("Failed to add string to object");
    }

    if (jsn_object_add_string(object2, "name", "Thomas")) {
        cr_assert_fail("Failed to add string to object");
    }
    if (jsn_object_add_number(object2, "age", 900)) {
        cr_assert_fail("Failed to add number to object");
    }
    if (jsn_object_add_string(object2, "city", "Paris")) {
        cr_assert_fail("Failed to add string to object");
    }

    if (jsn_object_add_string(object3, "name", "Bob")) {
        cr_assert_fail("Failed to add string to object");
    }
    if (jsn_object_add_number(object3, "age", 42)) {
        cr_assert_fail("Failed to add number to object");
    }
    if (jsn_object_add_string(object3, "city", "London")) {
        cr_assert_fail("Failed to add string to object");
    }
    json_object_t *obj_val1 = object1->obj_val;
    json_object_t *obj_val2 = object2->obj_val;
    json_object_t *obj_val3 = object3->obj_val;

    cr_assert_not_null(obj_val1);
    cr_assert_not_null(obj_val2);
    cr_assert_not_null(obj_val3);

    cr_assert_eq(obj_val1->size, 3);
    cr_assert_eq(obj_val2->size, 3);
    cr_assert_eq(obj_val3->size, 3);

    free(object1);
    free(object2);
    free(object3);

    json_object_t *list[] = {obj_val1, obj_val2, obj_val3, NULL};

    json_value_t *value = jsn_array_create_from_list_object(list, 3);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_ARRAY);
    cr_assert_not_null(value->arr_val);
    cr_assert_eq(value->arr_val->size, 3);
    cr_assert_not_null(value->arr_val->elem);

    cr_assert_eq(value->arr_val->elem[0].type, JSON_OBJECT);
    cr_assert_eq(value->arr_val->elem[0].obj_val->size, 3);
    cr_assert_str_eq(value->arr_val->elem[0].obj_val->keys[0], "name");
    cr_assert_eq(value->arr_val->elem[0].obj_val->values[0].type, JSON_STRING);
    cr_assert_str_eq(value->arr_val->elem[0].obj_val->values[0].str_val, "John");
    cr_assert_str_eq(value->arr_val->elem[0].obj_val->keys[1], "age");
    cr_assert_eq(value->arr_val->elem[0].obj_val->values[1].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[0].obj_val->values[1].nbr_val, 30);
    cr_assert_str_eq(value->arr_val->elem[0].obj_val->keys[2], "city");
    cr_assert_eq(value->arr_val->elem[0].obj_val->values[2].type, JSON_STRING);
    cr_assert_str_eq(value->arr_val->elem[0].obj_val->values[2].str_val, "New York");

    cr_assert_eq(value->arr_val->elem[1].type, JSON_OBJECT);
    cr_assert_eq(value->arr_val->elem[1].obj_val->size, 3);
    cr_assert_str_eq(value->arr_val->elem[1].obj_val->keys[0], "name");
    cr_assert_eq(value->arr_val->elem[1].obj_val->values[0].type, JSON_STRING);
    cr_assert_str_eq(value->arr_val->elem[1].obj_val->values[0].str_val, "Thomas");
    cr_assert_str_eq(value->arr_val->elem[1].obj_val->keys[1], "age");
    cr_assert_eq(value->arr_val->elem[1].obj_val->values[1].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[1].obj_val->values[1].nbr_val, 900);
    cr_assert_str_eq(value->arr_val->elem[1].obj_val->keys[2], "city");
    cr_assert_eq(value->arr_val->elem[1].obj_val->values[2].type, JSON_STRING);
    cr_assert_str_eq(value->arr_val->elem[1].obj_val->values[2].str_val, "Paris");

    cr_assert_eq(value->arr_val->elem[2].type, JSON_OBJECT);
    cr_assert_eq(value->arr_val->elem[2].obj_val->size, 3);
    cr_assert_str_eq(value->arr_val->elem[2].obj_val->keys[0], "name");
    cr_assert_eq(value->arr_val->elem[2].obj_val->values[0].type, JSON_STRING);
    cr_assert_str_eq(value->arr_val->elem[2].obj_val->values[0].str_val, "Bob");
    cr_assert_str_eq(value->arr_val->elem[2].obj_val->keys[1], "age");
    cr_assert_eq(value->arr_val->elem[2].obj_val->values[1].type, JSON_NUMBER);
    cr_assert_eq(value->arr_val->elem[2].obj_val->values[1].nbr_val, 42);
    cr_assert_str_eq(value->arr_val->elem[2].obj_val->keys[2], "city");
    cr_assert_eq(value->arr_val->elem[2].obj_val->values[2].type, JSON_STRING);
    cr_assert_str_eq(value->arr_val->elem[2].obj_val->values[2].str_val, "London");

    jsn_free(value);
}
