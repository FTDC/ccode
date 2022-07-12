cmake_minimum_required(VERSION 3.20)
project(ccode C)

set(CMAKE_C_STANDARD 11)

add_executable(ccode
        ccode/test.c
        ccode/var.c)

add_executable(test ccode/test.c)
add_executable(bool ccode/bool.c)
add_executable(gg ccode/gg.c)
add_executable(calc ccode/basic/calc.c)
add_executable(int ccode/basic/int.c)
add_executable(strcpy ccode/basic/strcpy.c)
add_executable(20220707 ccode/leetcode/20220707.c)
add_executable(maxNumber ccode/maxNumber.c)