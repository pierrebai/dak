
add_library(dak_any_op_tests SHARED
   src/any_tests.cpp
   src/compare_op_tests.cpp
   src/construct_op_tests.cpp
   src/convert_op_tests.cpp
   src/dominant_op_tests.cpp
   src/is_compatible_op_tests.cpp
   src/size_op_tests.cpp
   src/stream_op_tests.cpp
   src/to_text_op_tests.cpp

   include/dak/any_op/tests/helpers.h
)

target_link_libraries(dak_any_op_tests PUBLIC
   dak_any_op
   dak_utility
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_any_op_tests PROPERTY CXX_STANDARD 20)

target_include_directories(dak_any_op_tests PRIVATE
   include
)

