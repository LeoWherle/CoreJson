
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "corejson.h"


int main()
{
    const char *json_str2 =
        "{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}";
    const char *json_str =
        "{\"name\":\"John\",\"age\": [30 , 12 , 33],\"city\":\"New York\"}";

    JSONValue *json = parse_json(json_str);

    printf("------------\n");
    if (json->type != JSON_OBJECT) {
        printf("Error: Invalid JSON\n");
        return 1;
    }

    // // Accessing JSON data
    // for (size_t i = 0; i < json->object_value->size; i++) {
    //     printf("Key: %s, Value: ", json->object_value->keys[i]);
    //     if (json->object_value->properties[i].type == JSON_STRING) {
    //         printf("\"%s\"\n",
    //         json->object_value->properties[i].string_value);
    //     } else if (json->object_value->properties[i].type == JSON_NUMBER) {
    //         printf("%lf\n", json->object_value->properties[i].number_value);
    //     }
    // }

    print_json(json, 0);

    json_free(json);
    free(json);
    return 0;
}
