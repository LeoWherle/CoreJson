#include <stdio.h>
#include <unistd.h>
#include "corejson.h"

#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_output(void)
{
    cr_redirect_stdout();
}

Test(json_print, test_all, .init = redirect_all_output)
{
    const char *json = "{\"name\": \"John\",\"age\": 30,\"isMarried\": true,"
                       "\"hobbies\": [\"reading\",\"swimming\"]}";
    JSONValue *value = json_parse(json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    json_print(value, false, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str(json);
}

Test(json_print, test_all_format, .init = redirect_all_output)
{
    const char *json = "{\"name\": \"John\",\"age\": 30,\"isMarried\": true,"
                       "\"hobbies\": [\"reading\",\"swimming\"]}";
    JSONValue *value = json_parse(json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    json_print(value, true, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str("{\n"
                            "  \"name\": \"John\",\n"
                            "  \"age\": 30,\n"
                            "  \"isMarried\": true,\n"
                            "  \"hobbies\": [\n"
                            "    \"reading\",\n"
                            "    \"swimming\"\n"
                            "  ]\n"
                            "}");
}

Test(json_print, test_bool, .init = redirect_all_output)
{
    const char *json = "true";
    JSONValue *value = parse_value(&json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    json_print(value, false, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str("true");
}

Test(json_print, test_bool_format, .init = redirect_all_output)
{
    const char *json = "true";
    JSONValue *value = parse_value(&json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    json_print(value, true, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str("true");
}

Test(json_print, test_null, .init = redirect_all_output)
{
    const char *json = "null";
    JSONValue *value = parse_value(&json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    json_print(value, false, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str("null");
}

Test(json_print, test_null_format, .init = redirect_all_output)
{
    const char *json = "null";
    JSONValue *value = parse_value(&json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    json_print(value, true, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str("null");
}

Test(json_print, test_number, .init = redirect_all_output)
{
    const char *json = "123";
    JSONValue *value = parse_value(&json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    json_print(value, false, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str("123");
}

Test(json_print, test_number_format, .init = redirect_all_output)
{
    const char *json = "123";
    JSONValue *value = parse_value(&json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    json_print(value, true, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str("123");
}

Test(json_print, test_string, .init = redirect_all_output)
{
    const char *json = "\"hello, world!\"";
    JSONValue *value = parse_value(&json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    json_print(value, false, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str("\"hello, world!\"");
}

Test(json_print, test_string_format, .init = redirect_all_output)
{
    const char *json = "\"hello, world!\"";
    JSONValue *value = parse_value(&json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    json_print(value, true, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str("\"hello, world!\"");
}

Test(json_print, test_array, .init = redirect_all_output)
{
    const char *json = "[1,2,3]";
    JSONValue *value = parse_value(&json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    json_print(value, false, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str("[1,2,3]");
}

Test(json_print, test_array_format, .init = redirect_all_output)
{
    const char *json = "[1, 2, 3]";
    JSONValue *value = parse_value(&json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    json_print(value, true, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str("[\n"
                            "  1,\n"
                            "  2,\n"
                            "  3\n"
                            "]");
}

Test(json_print, test_big_number, .init = redirect_all_output)
{
    const char *json = "35678901234567600";
    JSONValue *value = parse_value(&json);
    if (value == NULL) {
        perror("Failed to parse JSON\n");
    }
    cr_assert_eq(value->type, JSON_NUMBER);
    cr_assert_eq(value->number_value, 35678901234567600.0);
    json_print(value, false, STDOUT_FILENO);
    json_free(value);
    cr_assert_stdout_eq_str("35678901234567600");
}
