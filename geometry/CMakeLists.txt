
add_library(dak_geometry
   include/dak/geometry/constants.h
   include/dak/geometry/edge.h
   include/dak/geometry/edges_map.h       src/edges_map.cpp
   include/dak/geometry/face.h            src/face.cpp
   include/dak/geometry/geometry_io.h     src/geometry_io.cpp
   include/dak/geometry/intersect.h       src/intersect.cpp
   include/dak/geometry/point.h           src/point.cpp
   include/dak/geometry/polygon.h         src/polygon.cpp
   include/dak/geometry/rectangle.h       src/rectangle.cpp
   include/dak/geometry/transform.h       src/transform.cpp
   include/dak/geometry/utility.h         src/utility.cpp
                                          src/filler.cpp
)

target_include_directories(dak_geometry PUBLIC
   include
)

target_link_libraries(dak_geometry dak_utility)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_geometry PROPERTY CXX_STANDARD 20)

