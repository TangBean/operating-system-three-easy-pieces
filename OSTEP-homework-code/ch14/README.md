# 第14章 插叙：内存操作API


## Homework (Code)

In this homework, you will gain some familiarity with memory allocation. First, you’ll write some buggy programs (fun!). Then, you’ll use
some tools to help you find the bugs you inserted. Then, you will realize
how awesome these tools are and use them in the future, thus making
yourself more happy and productive. The tools are the debugger (e.g.,
gdb) and a memory-bug detector called valgrind [SN05].

## Questions

1. First, write a simple program called null.c that creates a pointer
to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you
run this program?
2. Next, compile this program with symbol information included (with
the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information
about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing
run. What does gdb show you?
3. Finally, use the valgrind tool on this program. We’ll use the memcheck
tool that is a part of valgrind to analyze what happens. Run
this by typing in the following: valgrind --leak-check=yes
null. What happens when you run this? Can you interpret the
output from the tool?
4. Write a simple program that allocates memory using malloc() but
forgets to free it before exiting. What happens when this program
runs? Can you use gdb to find any problems with it? How about
valgrind (again with the --leak-check=yes flag)?
5. Write a program that creates an array of integers called data of size
100 using malloc; then, set data[100] to zero. What happens
when you run this program? What happens when you run this
program using valgrind? Is the program correct?
6. Create a program that allocates an array of integers (as above), frees
them, and then tries to print the value of one of the elements of
the array. Does the program run? What happens when you use
valgrind on it?
7. Now pass a funny value to free (e.g., a pointer in the middle of the
array you allocated above). What happens? Do you need tools to
find this type of problem?
8. 尝试其他接口分配内容，下一个 vector 数据结构，用 `realloc()` 管理内存，使用数组存储向量元素。

## Answers

#### Problem 1

> Reference null.c, null2.c

其中 null.c 对空指针执行了 free 操作，null2.c 对一个指向整型的指针执行了两次 free 操作。

null.c 可以正常运行，没啥错误。

null2.c 会：

```
$ ./null2
null2(5814,0x10c3c8dc0) malloc: *** error for object 0x7fd4514058b0: pointer being freed was not allocated
null2(5814,0x10c3c8dc0) malloc: *** set a breakpoint in malloc_error_break to debug
x=1[1]    5814 abort      ./null2
```

#### Problem 4

用 GDB 没啥问题。因为这个程序的运行时间很短，进程运行结束后，没有被回收的内存会被自动回收。

#### Problem 5

> Reference data100.c

不会报错，但是编译的时候会报 warning：

```
$ gcc -g data100.c -o data100
data100.c:13:35: warning: array index 100 is past the end of the array (which contains 100 elements) [-Warray-bounds]
    printf("Before: x[100]=%d\n", data[100]);
                                  ^    ~~~
data100.c:9:5: note: array 'data' declared here
    int data[100];
    ^
data100.c:14:5: warning: array index 100 is past the end of the array (which contains 100 elements) [-Warray-bounds]
    data[100] = 0;
    ^    ~~~
data100.c:9:5: note: array 'data' declared here
    int data[100];
    ^
data100.c:15:34: warning: array index 100 is past the end of the array (which contains 100 elements) [-Warray-bounds]
    printf("After: x[100]=%d\n", data[100]);
                                 ^    ~~~
data100.c:9:5: note: array 'data' declared here
    int data[100];
    ^
3 warnings generated.
```

运行结果：

```
$ ./data100                  
x[4]=100
Before: x[100]=-324749392
After: x[100]=0
After: *y=0
```

但是这是一个很危险的操作，`data[100]` 指向的空间如果已经被其他变量使用了，会导致无法预料测错误。

#### Problem 6

> Reference free_then_print.c

程序正常运行，和上题原因类似。

#### Problem 7

> Reference free_pointer.c

编译时不会报错，运行时会。

```
$ ./free_pointer 
data[4]=10
free_pointer(6494,0x117224dc0) malloc: *** error for object 0xa: pointer being freed was not allocated
free_pointer(6494,0x117224dc0) malloc: *** set a breakpoint in malloc_error_break to debug
[1]    6494 abort      ./free_pointer
```

#### Problem 8

> Reference vector.c, vector.h
