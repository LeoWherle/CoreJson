/*
** EPITECH PROJECT, 2023
** CoreJson [WSL: fedora]
** File description:
** jsn_dup_val
*/

#include <stdlib.h>
#include <string.h>
#include "corejson/internal.h"

// if dst is NULL, malloc a new json_value_t and return it, when failed return
// NULL and free dst (in both cases)
static json_value_t *jsn_dup_val(json_value_t *dst, const json_value_t *src)
{
    memcpy(dst, src, sizeof(json_value_t));
    if (src->type == JSON_OBJECT) {
        if (jsn_object_dup(dst, src) == JSN_ERROR) {
            jsn_free(dst);
            return NULL;
        }
    }
    if (src->type == JSON_ARRAY) {
        if (jsn_array_dup(dst, src) == JSN_ERROR) {
            jsn_free(dst);
            return NULL;
        }
    }
    return dst;
}

json_error_t jsn_object_dup(json_value_t *dst, const json_value_t *src)
{
    if (dst == NULL || src->obj_val == NULL || dst->obj_val == NULL)
        return JSN_ERROR;
    dst->obj_val->size = src->obj_val->size;
    dst->obj_val->keys = calloc(sizeof(char *), src->obj_val->size);
    dst->obj_val->values = calloc(sizeof(json_value_t), src->obj_val->size);
    if (dst->obj_val->keys == NULL || dst->obj_val->values == NULL) {
        free(dst->obj_val->keys);
        free(dst->obj_val->values);
        return JSN_ERROR;
    }
    for (uint32_t i = 0; i < src->obj_val->size; i++) {
        dst->obj_val->keys[i] = key_strdup(src->obj_val->keys[i]);
        if (dst->obj_val->keys[i] == NULL) {
            return JSN_ERROR;
        }
        if (!jsn_dup_val(&dst->obj_val->values[i], &src->obj_val->values[i])) {
            return JSN_ERROR;
        }
    }
    return JSN_SUCCESS;
}

json_error_t jsn_array_dup(json_value_t *dst, const json_value_t *src)
{
    if (dst == NULL || src->arr_val == NULL || dst->arr_val == NULL) {
        return JSN_ERROR;
    }
    dst->arr_val->size = src->arr_val->size;
    dst->arr_val->elem = calloc(sizeof(json_value_t), src->arr_val->size);
    if (dst->arr_val->elem == NULL) {
        DERR("calloc");
        return JSN_ERROR;
    }
    for (uint32_t i = 0; i < src->arr_val->size; i++) {
        // TODO: fix this
        // FLOG(stderr, "Dup element [%d] = %d\n", i, src->arr_val->elem[i].nbr_val);
        if (!jsn_dup_val(&dst->arr_val->elem[i], &src->arr_val->elem[i])) {
            FLOG(stderr, "Failed to duplicate array element\n");
            return JSN_ERROR;
        }
    }
    return JSN_SUCCESS;
}

json_value_t *jsn_dup(json_value_t *dst, const json_value_t *src)
{
    if (src == NULL) {
        return NULL;
    }
    if (dst == NULL) {
        if (src->type == JSON_OBJECT) {
            dst = jsn_object_create();
        }
        if (src->type == JSON_ARRAY) {
            dst = jsn_array_create();
        }
        if (src->type != JSON_OBJECT && src->type != JSON_ARRAY) {
            dst = malloc(sizeof(json_value_t));
        }
        if (dst == NULL) {
            return NULL;
        }
    }
    dst = jsn_dup_val(dst, src);
    return dst;
}
