
add_library(any_op_tests SHARED
   src/compare_op_tests.cpp
   src/convert_op_tests.cpp
   src/dominant_op_tests.cpp
   src/is_compatible_op_tests.cpp
   src/size_op_tests.cpp
   src/stream_op_tests.cpp
   src/to_text_op_tests.cpp

   include/dak/any_op/tests/helpers.h
)

target_link_libraries(any_op_tests PUBLIC
   any_op
)

set_property(TARGET any_op_tests PROPERTY CXX_STANDARD 20)

target_include_directories(any_op_tests PUBLIC
   include
   "${CMAKE_CURRENT_SOURCE_DIR}/../utility/include"
   "${CMAKE_CURRENT_SOURCE_DIR}/../any_op/include"
)

