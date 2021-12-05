
add_library(dak_object
   include/dak/object/all.h
   include/dak/object/array.h                   src/array.cpp
   include/dak/object/dict.h                    src/dict.cpp
   include/dak/object/element.h                 src/element.cpp
   include/dak/object/name.h                    src/name.cpp
   include/dak/object/name_stuff.h              src/name_stuff.cpp
   include/dak/object/namespace.h               src/namespace.cpp
   include/dak/object/object.h                  src/object.cpp
   include/dak/object/ref.h
   include/dak/object/weak_ref.h
   include/dak/object/valid_ref.h
   include/dak/object/edit_ref.h
   include/dak/object/ref_base.h                src/ref_base.cpp
   include/dak/object/ref_counted.h             src/ref_counted.cpp
   include/dak/object/ref_stream.h              src/ref_stream.cpp
   include/dak/object/similar.h                 src/similar.cpp
   include/dak/object/timeline.h
   include/dak/object/transaction.h             src/transaction.cpp
   include/dak/object/voc.h                     src/voc.cpp
   include/dak/object/voc_internal.h
)

target_include_directories(dak_object PUBLIC
   include
)

target_include_directories(dak_object PRIVATE
   include
   "${CMAKE_CURRENT_SOURCE_DIR}/../utility/include"
   "${CMAKE_CURRENT_SOURCE_DIR}/../any_op/include"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_object PROPERTY CXX_STANDARD 20)

