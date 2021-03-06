add_executable(
    rt_scheduler_test
    rt_scheduler_test.c
    $<TARGET_OBJECTS:rt_scheduler_objs>
)

target_include_directories(
    rt_scheduler_test
    PRIVATE
    $<TARGET_PROPERTY:rt_scheduler_objs,INCLUDE_DIRECTORIES>
)

target_compile_options(
    rt_scheduler_test
    PRIVATE
    -Wall
)
