cmake_minimum_required(VERSION 3.7.0)

# The dak/core library and its tests.

project(dak_utility)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

add_subdirectory(geometry)
add_subdirectory(geometry_tests)

add_subdirectory(utility)
add_subdirectory(utility_tests)

add_subdirectory(any_op)
add_subdirectory(any_op_tests)

add_subdirectory(ui)
add_subdirectory(ui_qt)

