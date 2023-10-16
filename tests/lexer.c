#include <criterion/criterion.h>
#include "corejson.h"

Test(json_lexer, test_next_token_number)
{
    const char *json = "123.45";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_NUMBER);
    cr_assert_eq(atof(token.value), 123.45);
}

Test(json_lexer, test_next_token_string)
{
    const char *json = "\"hello, world!\"";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_STRING);
    cr_assert_str_eq(token.value, "hello, world!");
}

Test(json_lexer, test_next_token_true)
{
    const char *json = "true";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_TRUE);
}

Test(json_lexer, test_next_token_false)
{
    const char *json = "false";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_FALSE);
}

Test(json_lexer, test_next_token_null)
{
    const char *json = "null";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_NULL);
}

Test(json_lexer, test_next_token_array)
{
    const char *json = "[1 , 2 , 3]";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_LEFT_BRACKET);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_NUMBER);
    cr_assert_eq(atoi(token.value), 1);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COMMA);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_NUMBER);
    cr_assert_eq(atoi(token.value), 2);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COMMA);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_NUMBER);
    cr_assert_eq(atoi(token.value), 3);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_RIGHT_BRACKET);
}

Test(json_lexer, test_next_token_object)
{
    const char *json = "{\"name\": \"John\", \"age\": 30}";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_LEFT_BRACE);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_STRING);
    cr_assert_str_eq(token.value, "name");
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COLON);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_STRING);
    cr_assert_str_eq(token.value, "John");
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COMMA);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_STRING);
    cr_assert_str_eq(token.value, "age");
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COLON);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_NUMBER);
    cr_assert_eq(atoi(token.value), 30);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_RIGHT_BRACE);
}

Test(json_lexer, test_next_token_error)
{
    const char *json = "hello";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_ERROR);
}

Test(json_lexer, test_next_token_empty_object)
{
    const char *json = "{}";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_LEFT_BRACE);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_RIGHT_BRACE);
}

Test(json_lexer, test_next_token_empty_array)
{
    const char *json = "[]";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_LEFT_BRACKET);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_RIGHT_BRACKET);
}

Test(json_lexer, test_next_token_empty_array_error)
{
    const char *json = "fayse";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_ERROR);
}

Test(json_lexer, test_next_token_nested_object)
{
    const char *json = "{\"name\": \"John\", \"address\": {\"city\": \"New "
                       "York\", \"state\": \"NY\"}}";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_LEFT_BRACE);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_STRING);
    cr_assert_str_eq(token.value, "name");
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COLON);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_STRING);
    cr_assert_str_eq(token.value, "John");
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COMMA);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_STRING);
    cr_assert_str_eq(token.value, "address");
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COLON);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_LEFT_BRACE);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_STRING);
    cr_assert_str_eq(token.value, "city");
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COLON);
}
Test(json_lexer, test_next_token_nested_array)
{
    const char *json = "[1, [2, 3], [4, [5, 6]]]";
    const char *p = json;
    token_t token;
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_LEFT_BRACKET);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_NUMBER);
    cr_assert_eq(atoi(token.value), 1);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COMMA);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_LEFT_BRACKET);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_NUMBER);
    cr_assert_eq(atoi(token.value), 2);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COMMA);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_NUMBER);
    cr_assert_eq(atoi(token.value), 3);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_RIGHT_BRACKET);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COMMA);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_LEFT_BRACKET);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_NUMBER);
    cr_assert_eq(atoi(token.value), 4);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COMMA);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_LEFT_BRACKET);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_NUMBER);
    cr_assert_eq(atoi(token.value), 5);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_COMMA);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_NUMBER);
    cr_assert_eq(atoi(token.value), 6);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_RIGHT_BRACKET);
    next_token(&p, &token);
    cr_assert_eq(token.type, TOKEN_RIGHT_BRACKET);
}
