
add_library(object_tests SHARED
   src/array_tests.cpp
   src/dict_tests.cpp
   src/element_tests.cpp
   src/name_tests.cpp
   src/namespace_tests.cpp
   src/object_tests.cpp
   src/ref_stream_tests.cpp
   src/transaction_tests.cpp
   include/dak/object/tests/helpers.h
)

target_link_libraries(object_tests PUBLIC
   object
   any_op
   utility
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET object_tests PROPERTY CXX_STANDARD 20)

target_include_directories(object_tests PUBLIC
   include
   "${CMAKE_CURRENT_SOURCE_DIR}/../utility/include"
   "${CMAKE_CURRENT_SOURCE_DIR}/../any_op/include"
   "${CMAKE_CURRENT_SOURCE_DIR}/../object/include"
)

