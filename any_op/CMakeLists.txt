
add_library(any_op
   Readme.md
   include/dak/any_op/compare_op.h            src/compare_op.cpp
   include/dak/any_op/convert_op.h            src/convert_op.cpp
   include/dak/any_op/dominant_op.h           src/dominant_op.cpp
   include/dak/any_op/is_compatible_op.h      src/is_compatible_op.cpp
   include/dak/any_op/op.h
   include/dak/any_op/op_selector.h           src/register_ops.cpp
   include/dak/any_op/size_op.h               src/size_op.cpp
   include/dak/any_op/stream_op.h             src/ostream_op.cpp
                                              src/istream_op.cpp
   include/dak/any_op/to_text_op.h            src/to_text_op.cpp
)

target_include_directories(any_op PUBLIC
   include
   "${CMAKE_CURRENT_SOURCE_DIR}/../utility/include"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET any_op PROPERTY CXX_STANDARD 20)

target_compile_options(any_op PRIVATE
   /bigobj
)

