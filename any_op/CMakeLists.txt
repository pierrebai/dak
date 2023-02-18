
add_library(dak_any_op
   Readme.md
   include/dak/any_op/all.h
   include/dak/any_op/as_op.h
   include/dak/any_op/compare_op.h            src/compare_op.cpp
   include/dak/any_op/construct_op.h          src/construct_op.cpp
   include/dak/any_op/convert_op.h            src/convert_op.cpp
   include/dak/any_op/dominant_op.h           src/dominant_op.cpp
   include/dak/any_op/is_compatible_op.h      src/is_compatible_op.cpp
   include/dak/any_op/is_integer_op.h         src/is_integer_op.cpp
   include/dak/any_op/is_real_op.h            src/is_real_op.cpp
   include/dak/any_op/is_unsigned_op.h        src/is_unsigned_op.cpp
   include/dak/any_op/op.h
   include/dak/any_op/op_makers.h
   include/dak/any_op/op_selector.h           src/register_ops.cpp
   include/dak/any_op/size_op.h               src/size_op.cpp
   include/dak/any_op/stream_op.h             src/ostream_op.cpp
                                              src/istream_op.cpp
   include/dak/any_op/supers_of_op.h          src/supers_of_op.cpp
   include/dak/any_op/to_text_op.h            src/to_text_op.cpp
)

target_include_directories(dak_any_op PUBLIC
   include
)

target_link_libraries(dak_any_op dak_utility)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_any_op PROPERTY CXX_STANDARD 20)

target_compile_options(dak_any_op PRIVATE
   /bigobj
)

