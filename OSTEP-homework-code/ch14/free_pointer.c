/*
 * Created by Tang_Bean on 2020/9/20.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int data[100];
    data[4] = 10;
    printf("data[4]=%d\n", data[4]);
    free(&data[4]);
    return 0;
}
