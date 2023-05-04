
add_library(dak_utility_tests SHARED
   src/get_type_info_tests.cpp
   src/get_type_name_tests.cpp
   src/multi_thread_progress_tests.cpp
   src/number_tests.cpp
   src/progress_tests.cpp
   src/stopwatch_tests.cpp
   src/stream_progress_tests.cpp
   src/text_tests.cpp
   src/thread_pool_tests.cpp
   src/sequential_worker_tests.cpp
   src/sequential_items_worker_tests.cpp
   src/threaded_worker_tests.cpp
   src/threaded_items_worker_tests.cpp
   src/undo_stack_tests.cpp

   include/dak/utility/tests/helpers.h
)

target_link_libraries(dak_utility_tests PUBLIC
   dak_utility
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_utility_tests PROPERTY CXX_STANDARD 20)

target_include_directories(dak_utility_tests PRIVATE
   include
)
