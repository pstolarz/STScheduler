cmake_minimum_required(VERSION 2.8)
project("RTScheduler")

add_library(
    rt_scheduler_objs
    OBJECT
    rt_scheduler.c
)

target_include_directories(
    rt_scheduler_objs
    PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_compile_options(
    rt_scheduler_objs
    PRIVATE
    -Wall
)

add_subdirectory(test)
