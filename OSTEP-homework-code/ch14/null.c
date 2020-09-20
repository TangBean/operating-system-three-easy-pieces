/*
 * Created by Tang_Bean on 2020/9/20.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int *x = (int*) calloc(1, sizeof(int));
    x = NULL;
    printf("%d", *x);
    free(x);
    return 0;
}
