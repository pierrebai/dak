
add_library(dak_object_io_tests SHARED
   src/ref_istream_tests.cpp
   src/ref_ostream_tests.cpp
   include/dak/object_io/tests/helpers.h
)

target_link_libraries(dak_object_io_tests PUBLIC
   dak_object_io
   dak_object
   dak_any_op
   dak_utility
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_object_io_tests PROPERTY CXX_STANDARD 20)

target_include_directories(dak_object_io_tests PUBLIC
   include
)

