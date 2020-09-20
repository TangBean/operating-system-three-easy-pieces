cmake_minimum_required(VERSION 3.17)
project(OSTEP_homework_code C)

set(CMAKE_C_STANDARD 99)

add_executable(OSTEP_homework_code main.c ch14/null.c ch14/forget_free.c ch14/null2.c ch14/data100.c ch14/free_then_print.c ch14/free_pointer.c ch14/vector.c ch14/vector.h)