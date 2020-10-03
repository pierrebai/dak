cmake_minimum_required(VERSION 3.7.0)

# The dak/core library and its tests.

project(dak_utility)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

add_subdirectory(utility)
add_subdirectory(utility_tests)

