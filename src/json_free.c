#include <stdlib.h>
#include "corejson.h"

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
                json_free(&jsonValue->object_value->values[i]);
                free(jsonValue->object_value->keys[i]);
            }
            free(jsonValue->object_value->values);
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
