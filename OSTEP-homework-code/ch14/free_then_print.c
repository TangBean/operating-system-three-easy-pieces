/*
 * Created by Tang_Bean on 2020/9/20.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int *x = (int*) malloc(100 * sizeof(int));
    free(x);
    int  *y = x;
    y += 10;
    printf("x[10]=%d\n", *y);
    return 0;
}
