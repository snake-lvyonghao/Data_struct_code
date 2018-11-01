cmake_minimum_required(VERSION 3.6)
project(data_struct C)

set(CMAKE_C_STANDARD 99)

add_executable(data_struct main.c)
add_executable(LinkList 数据结构源码/LinkList.c 数据结构源码/Triple.c)
add_executable(stack 数据结构源码/stack.c)
add_executable(queue 数据结构源码/Queue.c)
add_executable(Triple 数据结构源码/Triple.c)