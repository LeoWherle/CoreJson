#include "corejson_internal.h"
#include "builder/corejson_array.h"

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
    cr_assert_not_null(value->array_value);
    cr_assert_eq(value->array_value->size, 3);
    cr_assert_not_null(value->array_value->elements);
    cr_assert_eq(value->array_value->elements[0].type, JSON_STRING);
    cr_assert_str_eq(value->array_value->elements[0].string_value, "Hello");
    cr_assert_eq(value->array_value->elements[1].type, JSON_STRING);
    cr_assert_str_eq(value->array_value->elements[1].string_value, "World");
    cr_assert_eq(value->array_value->elements[2].type, JSON_STRING);
    cr_assert_str_eq(value->array_value->elements[2].string_value, "!");
    jsn_free(value);
}


Test(jsn_array_create_from_list, number)
{
    double list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    json_value_t *value = jsn_array_create_from_list_number(list, 9);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_ARRAY);
    cr_assert_not_null(value->array_value);
    cr_assert_eq(value->array_value->size, 9);
    cr_assert_not_null(value->array_value->elements);
    cr_assert_eq(value->array_value->elements[0].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[0].number_value, 1);
    cr_assert_eq(value->array_value->elements[1].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[1].number_value, 2);
    cr_assert_eq(value->array_value->elements[2].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[2].number_value, 3);
    cr_assert_eq(value->array_value->elements[3].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[3].number_value, 4);
    cr_assert_eq(value->array_value->elements[4].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[4].number_value, 5);
    cr_assert_eq(value->array_value->elements[5].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[5].number_value, 6);
    cr_assert_eq(value->array_value->elements[6].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[6].number_value, 7);
    cr_assert_eq(value->array_value->elements[7].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[7].number_value, 8);
    cr_assert_eq(value->array_value->elements[8].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[8].number_value, 9);
    jsn_free(value);
}

Test(jsn_array_create_from_list, boolean)
{
    bool list[] = {true, false, true, false, true, false, true, false, true};
    json_value_t *value = jsn_array_create_from_list_bool(list, 9);

    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_ARRAY);
    cr_assert_not_null(value->array_value);
    cr_assert_eq(value->array_value->size, 9);
    cr_assert_not_null(value->array_value->elements);
    cr_assert_eq(value->array_value->elements[0].type, JSON_BOOL);
    cr_assert_eq(value->array_value->elements[0].bool_value, true);
    cr_assert_eq(value->array_value->elements[1].type, JSON_BOOL);
    cr_assert_eq(value->array_value->elements[1].bool_value, false);
    cr_assert_eq(value->array_value->elements[2].type, JSON_BOOL);
    cr_assert_eq(value->array_value->elements[2].bool_value, true);
    cr_assert_eq(value->array_value->elements[3].type, JSON_BOOL);
    cr_assert_eq(value->array_value->elements[3].bool_value, false);
    cr_assert_eq(value->array_value->elements[4].type, JSON_BOOL);
    cr_assert_eq(value->array_value->elements[4].bool_value, true);
    cr_assert_eq(value->array_value->elements[5].type, JSON_BOOL);
    cr_assert_eq(value->array_value->elements[5].bool_value, false);
    cr_assert_eq(value->array_value->elements[6].type, JSON_BOOL);
    cr_assert_eq(value->array_value->elements[6].bool_value, true);
    cr_assert_eq(value->array_value->elements[7].type, JSON_BOOL);
    cr_assert_eq(value->array_value->elements[7].bool_value, false);
    cr_assert_eq(value->array_value->elements[8].type, JSON_BOOL);
    cr_assert_eq(value->array_value->elements[8].bool_value, true);
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
    json_object_t *obj_val1 = object1->object_value;
    json_object_t *obj_val2 = object2->object_value;
    json_object_t *obj_val3 = object3->object_value;

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
    cr_assert_not_null(value->array_value);
    cr_assert_eq(value->array_value->size, 3);
    cr_assert_not_null(value->array_value->elements);

    cr_assert_eq(value->array_value->elements[0].type, JSON_OBJECT);
    cr_assert_eq(value->array_value->elements[0].object_value->size, 3);
    cr_assert_str_eq(value->array_value->elements[0].object_value->keys[0], "name");
    cr_assert_eq(value->array_value->elements[0].object_value->values[0].type, JSON_STRING);
    cr_assert_str_eq(value->array_value->elements[0].object_value->values[0].string_value, "John");
    cr_assert_str_eq(value->array_value->elements[0].object_value->keys[1], "age");
    cr_assert_eq(value->array_value->elements[0].object_value->values[1].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[0].object_value->values[1].number_value, 30);
    cr_assert_str_eq(value->array_value->elements[0].object_value->keys[2], "city");
    cr_assert_eq(value->array_value->elements[0].object_value->values[2].type, JSON_STRING);
    cr_assert_str_eq(value->array_value->elements[0].object_value->values[2].string_value, "New York");

    cr_assert_eq(value->array_value->elements[1].type, JSON_OBJECT);
    cr_assert_eq(value->array_value->elements[1].object_value->size, 3);
    cr_assert_str_eq(value->array_value->elements[1].object_value->keys[0], "name");
    cr_assert_eq(value->array_value->elements[1].object_value->values[0].type, JSON_STRING);
    cr_assert_str_eq(value->array_value->elements[1].object_value->values[0].string_value, "Thomas");
    cr_assert_str_eq(value->array_value->elements[1].object_value->keys[1], "age");
    cr_assert_eq(value->array_value->elements[1].object_value->values[1].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[1].object_value->values[1].number_value, 900);
    cr_assert_str_eq(value->array_value->elements[1].object_value->keys[2], "city");
    cr_assert_eq(value->array_value->elements[1].object_value->values[2].type, JSON_STRING);
    cr_assert_str_eq(value->array_value->elements[1].object_value->values[2].string_value, "Paris");

    cr_assert_eq(value->array_value->elements[2].type, JSON_OBJECT);
    cr_assert_eq(value->array_value->elements[2].object_value->size, 3);
    cr_assert_str_eq(value->array_value->elements[2].object_value->keys[0], "name");
    cr_assert_eq(value->array_value->elements[2].object_value->values[0].type, JSON_STRING);
    cr_assert_str_eq(value->array_value->elements[2].object_value->values[0].string_value, "Bob");
    cr_assert_str_eq(value->array_value->elements[2].object_value->keys[1], "age");
    cr_assert_eq(value->array_value->elements[2].object_value->values[1].type, JSON_NUMBER);
    cr_assert_eq(value->array_value->elements[2].object_value->values[1].number_value, 42);
    cr_assert_str_eq(value->array_value->elements[2].object_value->keys[2], "city");
    cr_assert_eq(value->array_value->elements[2].object_value->values[2].type, JSON_STRING);
    cr_assert_str_eq(value->array_value->elements[2].object_value->values[2].string_value, "London");

    jsn_free(value);
}
