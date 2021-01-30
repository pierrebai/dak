
add_library(geometry
   include/dak/geometry/constants.h
   include/dak/geometry/edge.h
   include/dak/geometry/edges_map.h       src/edges_map.cpp
   include/dak/geometry/face.h            src/face.cpp
   include/dak/geometry/intersect.h       src/intersect.cpp
   include/dak/geometry/point.h           src/point.cpp
   include/dak/geometry/polygon.h         src/polygon.cpp
   include/dak/geometry/rectangle.h       src/rectangle.cpp
   include/dak/geometry/transform.h       src/transform.cpp
   include/dak/geometry/utility.h         src/utility.cpp
                                          src/filler.cpp
)

target_include_directories(geometry PUBLIC
   include
   "${CMAKE_CURRENT_SOURCE_DIR}/../utility/include"
)

set_property(TARGET geometry PROPERTY CXX_STANDARD 20)

