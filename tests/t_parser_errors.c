#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "corejson_internal.h"

static void redirect_all_output(void)
{
    // cr_redirect_stderr();
    cr_redirect_stdout();
}

Test(json_parser, test_parse_number_error, .init = redirect_all_output)
{
    const char *json = "-";
    json_value_t *value = jsn_parse_value(&json);
    cr_assert_not_null(value);
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->number_value, 0);
    jsn_free(value);
}

Test(json_parser, test_parse_big_string_error, .init = redirect_all_output)
{
    const char *json =
        "\"01234567890123456789012345678901234567890123456789012345678901234567"
        "8901234567890123456789012345678901234567890123456789012345678901234567"
        "8901234567890123456789012345678901234567890123456789012345678901234567"
        "8901234567890123456789012345678901234567890123456789\"";
    json_value_t *value = jsn_parse_value(&json);
    cr_assert_null(value);
    jsn_free(value);
}

Test(json_parser_error, test_array_in_object_missing_value,
    .init = redirect_all_output)
{
    const char *json = "{\"slalu\" : [1, 2 , 3,]}";
    json_value_t *value = jsn_parse(json);
    cr_assert_null(value);
    jsn_free(value);
}
Test(json_parser_error, test_array_missing_value, .init = redirect_all_output)
{
    const char *json = "[1, 2 , 3,]";
    json_value_t *value = jsn_parse_value(&json);
    cr_assert_null(value);
    jsn_free(value);
}

Test(json_parser_error, test_object_missing_key, .init = redirect_all_output)
{
    const char *json = "{\"x\": 1, \"y\": 2, }";
    json_value_t *value = jsn_parse(json);
    cr_assert_null(value);
    jsn_free(value);
}
Test(json_parser_error, test_object_missing_value, .init = redirect_all_output)
{
    const char *json = "{\"x\": \"1\", \"y\":  }";
    json_value_t *value = jsn_parse(json);
    cr_assert_null(value);
    jsn_free(value);
}
Test(json_parser_error, test_object_missing_colon, .init = redirect_all_output)
{
    const char *json = "{\"x\": \"1\", \"y\"  }";
    json_value_t *value = jsn_parse(json);
    cr_assert_null(value);
    jsn_free(value);
}
Test(json_parser_error, test_object_in_object_missing_value,
    .init = redirect_all_output)
{
    const char *json = "{\"slalu\" : {\"x\": 1, \"y\": 2, }}";
    json_value_t *value = jsn_parse(json);
    cr_assert_null(value);
    jsn_free(value);
}
