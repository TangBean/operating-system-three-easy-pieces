/*
 * Created by Tang_Bean on 2020/9/20.
 */

#ifndef OSTEP_HOMEWORK_CODE_VECTOR_H
#define OSTEP_HOMEWORK_CODE_VECTOR_H

#include <stdio.h>
#include <stdlib.h>

struct vector {
    int *data;
    int size;
    int capacity;
};

/**
 * 添加元素：
 * 1. 检查是否需要扩容
 * 2. data 中添加元素
 */
void vector_append(struct vector *v, int value) {
    if (v->size == v->capacity) {
        v->capacity = v->capacity * 2;
        v->data = realloc(v->data, v->capacity * sizeof(int));
    }
    v->data[v->size++] = value;
}

/**
 * 删除元素：
 * 1. data 中删除元素
 * 2. 检查是否需要缩容
 */
void vector_delEnd(struct vector *v) {
    v->data[v->size--] = 0;
    if (v->size == (int) (v->capacity / 4)) {
        v->capacity = v->capacity / 2;
        v->data = realloc(v->data, v->capacity * sizeof(int));
    }
}

void vector_free(struct vector *v) {
    free(v->data);
    v->size = 0;
    v->capacity = 0;
}

void print_vector(struct vector *v) {
    printf("size: %d\n", v->size);
    printf("capacity: %d\n", v->capacity);
    for (int i = 0; i < v->size; i++) {
        printf("data[%d]: %d\n", i, v->data[i]);
    }
}

#endif //OSTEP_HOMEWORK_CODE_VECTOR_H
