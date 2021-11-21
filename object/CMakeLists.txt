
add_library(object
   include/dak/object/all.h
   include/dak/object/array.h                   src/array.cpp
   include/dak/object/dict.h                    src/dict.cpp
   include/dak/object/element.h                 src/element.cpp
   include/dak/object/name.h                    src/name.cpp
   include/dak/object/object.h                  src/object.cpp
   include/dak/object/ref.h                     src/ref_base.cpp
   include/dak/object/ref_counted.h             src/ref_counted.cpp
   include/dak/object/ref_stream.h              src/ref_stream.cpp
   include/dak/object/stream.h                  src/stream.cpp
   include/dak/object/timeline.h
   include/dak/object/transaction.h             src/transaction.cpp
   include/dak/object/voc.h                     src/voc.cpp
   include/dak/object/voc_internal.h
)

target_include_directories(object PUBLIC
   include
   "${CMAKE_CURRENT_SOURCE_DIR}/../utility/include"
)

set_property(TARGET object PROPERTY CXX_STANDARD 20)

