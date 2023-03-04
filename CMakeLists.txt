cmake_minimum_required(VERSION 2.8)
project("STScheduler")

add_library(
    st_scheduler_objs
    OBJECT
    st_scheduler.c
)

target_include_directories(
    st_scheduler_objs
    PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_compile_options(
    st_scheduler_objs
    PRIVATE
    -Wall
)

add_subdirectory(test)
