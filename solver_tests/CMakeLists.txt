
add_library(solver_tests SHARED
   src/solve_tests.cpp
)

target_link_libraries(solver_tests PUBLIC
   dak_solver
   dak_utility
)

target_compile_features(solver_tests PUBLIC cxx_std_20)
