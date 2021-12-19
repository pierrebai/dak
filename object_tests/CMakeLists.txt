
add_library(dak_object_tests SHARED
   src/array_tests.cpp
   src/dict_tests.cpp
   src/value_tests.cpp
   src/value_conversion_tests.cpp
   src/value_ensure_tests.cpp
   src/value_function_tests.cpp
   src/make_op_tests.cpp
   src/name_tests.cpp
   src/namespace_tests.cpp
   src/object_tests.cpp
   src/ref_tests.cpp
   src/transaction_tests.cpp
   include/dak/object/tests/data.h
   include/dak/object/tests/helpers.h
)

target_link_libraries(dak_object_tests PUBLIC
   dak_object_io
   dak_object
   dak_any_op
   dak_utility
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_object_tests PROPERTY CXX_STANDARD 20)

target_include_directories(dak_object_tests PRIVATE
   include
)

