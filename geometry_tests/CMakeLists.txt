
add_library(dak_geometry_tests SHARED
   src/edge_tests.cpp
   src/edges_map_tests.cpp
   src/face_tests.cpp
   src/intersect_tests.cpp
   src/point_tests.cpp
   src/polygon_tests.cpp
   src/rectangle_tests.cpp
   src/utility_tests.cpp
)

target_link_libraries(dak_geometry_tests PUBLIC
   dak_geometry
   dak_utility
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_geometry_tests PROPERTY CXX_STANDARD 20)

target_include_directories(dak_geometry_tests PRIVATE
   include
)

