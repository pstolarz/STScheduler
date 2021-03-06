cmake_minimum_required(VERSION 2.8)
project("rt_sched")

add_library(
    rt_sched_objs
    OBJECT
    rt_sched.c
)

target_include_directories(
    rt_sched_objs
    PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_compile_options(
    rt_sched_objs
    PRIVATE
    -Wall
)

add_subdirectory(test)
