cmake_minimum_required(VERSION 3.6)
project(data_struct C)

set(CMAKE_C_STANDARD 99)

add_executable(data_struct main.c)
add_executable(LinkList 数据结构源码/LinkList.c)
add_executable(stack 数据结构源码/stack.c)
add_executable(queue 数据结构源码/Queue.c)
add_executable(Triple 数据结构源码/Triple.c)
add_executable(Binary 数据结构源码/BinaryTree.c)
add_executable(ThreadedBinaryTree 数据结构源码/ThreadedBinaryTree.c)
add_executable(MGraph 数据结构源码/MGraph.c)
add_executable(ListGraph 数据结构源码/ListGraph.c)