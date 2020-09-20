/*
 * Created by Tang_Bean on 2020/9/20.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int *x = (int*) malloc(sizeof(int));
    *x = 1;
    printf("x=%d", *x);
    free(x);
    free(x);
    return 0;
}
