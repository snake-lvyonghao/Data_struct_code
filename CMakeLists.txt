cmake_minimum_required(VERSION 3.6)
project(data_struct C)

set(CMAKE_C_STANDARD 99)

add_executable(data_struct main.c )
add_executable(LinkList 数据结构源码/LinkList.c)
add_executable(stack 数据结构源码/stack.c)