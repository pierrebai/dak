
add_library(dak_command
   include/dak/command/command.h                 src/command.cpp
   include/dak/command/command_tree.h            src/command_tree.cpp
   include/dak/command/command_work_item.h       src/command_work_item.cpp
                                                 src/command_ops.cpp
   include/dak/command/types.h
)

target_include_directories(dak_command PUBLIC
   include
)

target_link_libraries(dak_command dak_object)
target_link_libraries(dak_command dak_utility)
target_link_libraries(dak_command dak_any_op)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_command PROPERTY CXX_STANDARD 20)
