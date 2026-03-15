
add_library(dak_solver
   src/solve.cpp
)

target_include_directories(dak_solver PUBLIC
   include
)

target_link_libraries(dak_solver dak_utility)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_solver PROPERTY CXX_STANDARD 20)

