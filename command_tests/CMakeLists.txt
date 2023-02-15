
add_library(dak_command_tests SHARED
   src/command_tree_tests.cpp
   include/dak/command/tests/helpers.h
)

target_link_libraries(dak_command_tests PUBLIC
   dak_command
   dak_object_io
   dak_object
   dak_any_op
   dak_utility
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_command_tests PROPERTY CXX_STANDARD 20)

target_include_directories(dak_command_tests PUBLIC
   include
)

