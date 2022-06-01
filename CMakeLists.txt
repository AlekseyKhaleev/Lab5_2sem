cmake_minimum_required(VERSION 3.22)
project(Lab5_2)

set(CMAKE_CXX_STANDARD 17)

find_library(LIB_TO_INCLUDE library /home/kristofer/2_sem_prog/Lab5_2/Lib)
find_path (LIB_INCLUDES lib_table.h lib_classes.h lib_exceptions.h lib_definitions.h lib_print_func.h lib_draw_func.h /home/kristofer/2_sem_prog/Lab5_2/Lib/headers)
include_directories(${LIB_INCLUDES})

add_executable(Lab5_2 Lab5_2.cpp lib_classes.cpp lib_table.cpp)

target_link_libraries(Lab5_2 ${LIB_TO_INCLUDE})