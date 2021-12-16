cmake_minimum_required(VERSION 3.7.0)

option(want_qt "Control if Qt library is built." 1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The dak libraries and their tests.

project(dak)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

add_subdirectory(geometry)
add_subdirectory(geometry_tests)

add_subdirectory(utility)
add_subdirectory(utility_tests)

add_subdirectory(object)
add_subdirectory(object_tests)

add_subdirectory(object_io)
add_subdirectory(object_io_tests)

add_subdirectory(any_op)
add_subdirectory(any_op_tests)

add_subdirectory(ui)

if(want_qt)
   add_subdirectory(ui_qt)
endif()

