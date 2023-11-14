#include <criterion/criterion.h>
#include "corejson/internal.h"

// Test(jsn_object_dup, number)
// {
//     json_value_t *object = NULL;
//     json_value_t *object2 = NULL;

//     object = jsn_object_create();

//     cr_assert_eq(jsn_object_add_number(object, "value", 1), JSN_SUCCESS);
//     cr_assert_not_null(object);
//     cr_assert_eq(object->obj_val->size, 1);
//     cr_assert_eq(object->obj_val->values[0].type, JSON_NUMBER);
//     cr_assert_eq(object->obj_val->values[0].nbr_val, 1);
//     cr_assert_str_eq(object->obj_val->keys[0], "value");

//     object2 = jsn_object_create();
//     cr_assert_not_null(object2);
//     cr_assert_eq(jsn_object_dup(object2, object), JSN_SUCCESS);

//     cr_assert_not_null(object2);
//     cr_assert_eq(object2->obj_val->size, 1);
//     cr_assert_eq(object2->obj_val->values[0].type, JSON_NUMBER);
//     cr_assert_eq(object2->obj_val->values[0].nbr_val, 1);
//     cr_assert_str_eq(object2->obj_val->keys[0], "value");

//     jsn_free(object);
//     jsn_free(object2);
// }
