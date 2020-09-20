/*
 * Created by Tang_Bean on 2020/9/20.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int data[100];
    data[4] = 100;
    printf("x[4]=%d\n", data[4]);

    printf("Before: x[100]=%d\n", data[100]);
    data[100] = 0;
    printf("After: x[100]=%d\n", data[100]);
    int *y = data;
    y += 100;
    printf("After: *y=%d\n", *y);
}
