
add_library(geometry_tests SHARED
   src/edge_tests.cpp
   src/edges_map_tests.cpp
   src/face_tests.cpp
   src/intersect_tests.cpp
   src/point_tests.cpp
   src/polygon_tests.cpp
   src/rectangle_tests.cpp
   src/utility_tests.cpp
)

target_link_libraries(geometry_tests PUBLIC
   geometry
   utility
)

target_compile_features(geometry_tests PUBLIC
   cxx_std_20
)

target_include_directories(geometry_tests PUBLIC
   include
   "${PROJECT_SOURCE_DIR}/geometry/include"
)

