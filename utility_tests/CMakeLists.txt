
add_library(utility_tests SHARED
   src/multi_thread_progress_tests.cpp
   src/number_tests.cpp
   src/progress_tests.cpp
   src/stopwatch_tests.cpp
   src/stream_progress_tests.cpp
   src/text_tests.cpp
   src/thread_pool_tests.cpp
   src/threaded_work_tests.cpp
   src/undo_stack_tests.cpp
)

target_link_libraries(utility_tests PUBLIC
   utility
)

target_compile_features(utility_tests PUBLIC cxx_std_20)

target_include_directories(utility_tests PUBLIC
   "${CMAKE_CURRENT_SOURCE_DIR}/../utility/include"
)

