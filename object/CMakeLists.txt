
add_library(dak_object
   include/dak/object/all.h
   include/dak/object/array.h                   src/array.cpp
   include/dak/object/dict.h                    src/dict.cpp
   include/dak/object/make_op.h
   include/dak/object/name.h                    src/name.cpp
   include/dak/object/exact_name.h              src/exact_name.cpp
   include/dak/object/name_stuff.h              src/name_stuff.cpp
   include/dak/object/namespace.h               src/namespace.cpp
   include/dak/object/object.h                  src/object.cpp
                                                src/object_ops.cpp
   include/dak/object/ref.h
   include/dak/object/weak_ref.h
   include/dak/object/valid_ref.h
   include/dak/object/edit_ref.h
   include/dak/object/ref_base.h                src/ref_base.cpp
   include/dak/object/ref_counted.h             src/ref_counted.cpp
   include/dak/object/ref_input.h               src/ref_input.cpp
   include/dak/object/ref_istream.h             src/ref_istream.cpp
   include/dak/object/ref_istream_op.h          src/ref_istream_op.cpp
   include/dak/object/ref_ostream.h             src/ref_ostream.cpp
   include/dak/object/ref_ostream_op.h          src/ref_ostream_op.cpp
   include/dak/object/ref_output.h              src/ref_output.cpp
   include/dak/object/similar.h                 src/similar.cpp
   include/dak/object/timeline.h
   include/dak/object/transaction.h             src/transaction.cpp
   include/dak/object/value.h                   src/value.cpp
   include/dak/object/voc.h                     src/voc.cpp
   include/dak/object/voc_internal.h
)

target_include_directories(dak_object PUBLIC
   include
)

target_link_libraries(dak_object dak_utility)
target_link_libraries(dak_object dak_any_op)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_object PROPERTY CXX_STANDARD 20)

