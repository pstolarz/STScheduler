add_executable(
    rt_sched_test
    rt_sched_test.c
    $<TARGET_OBJECTS:rt_sched_objs>
)

target_include_directories(
    rt_sched_test
    PRIVATE
    $<TARGET_PROPERTY:rt_sched_objs,INCLUDE_DIRECTORIES>
)

target_compile_options(
    rt_sched_test
    PRIVATE
    -Wall
)
