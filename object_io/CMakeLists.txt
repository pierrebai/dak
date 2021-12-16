
add_library(dak_object_io
   include/dak/object_io/all.h
   include/dak/object_io/ref_input.h               src/ref_input.cpp
   include/dak/object_io/ref_istream.h             src/ref_istream.cpp
   include/dak/object_io/ref_istream_op.h          src/ref_istream_op.cpp
   include/dak/object_io/ref_ostream.h             src/ref_ostream.cpp
   include/dak/object_io/ref_ostream_op.h          src/ref_ostream_op.cpp
   include/dak/object_io/ref_output.h              src/ref_output.cpp
)

target_include_directories(dak_object_io PUBLIC
   include
)

target_link_libraries(dak_object_io dak_object)
target_link_libraries(dak_object_io dak_utility)
target_link_libraries(dak_object_io dak_any_op)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_object_io PROPERTY CXX_STANDARD 20)
