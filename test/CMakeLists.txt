add_executable(
    st_scheduler_test
    st_scheduler_test.c
    $<TARGET_OBJECTS:st_scheduler_objs>
)

target_include_directories(
    st_scheduler_test
    PRIVATE
    $<TARGET_PROPERTY:st_scheduler_objs,INCLUDE_DIRECTORIES>
)

target_compile_options(
    st_scheduler_test
    PRIVATE
    -Wall
)
