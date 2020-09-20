/*
 * Created by Tang_Bean on 2020/9/20.
 */

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(int argc, char *argv[]) {
    struct vector v = {
            .data = (int*) malloc(sizeof(int)),
            .size = 1,
            .capacity = 1
    };
    v.data[0] = 4;
    struct vector *vp = &v;

    vector_append(vp, 1);
    vector_append(vp, 2);
    vector_append(vp, 3);
    vector_delEnd(vp);

    print_vector(vp);

    vector_delEnd(vp);
    vector_delEnd(vp);

    print_vector(vp);

    vector_free(vp);

    return 0;
}
