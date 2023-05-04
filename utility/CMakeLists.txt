
add_library(dak_utility
   include/dak/utility/all.h
   include/dak/utility/constants.h
   include/dak/utility/containers.h
   include/dak/utility/number.h
   include/dak/utility/progress.h                  src/progress.cpp
   include/dak/utility/stream_progress.h           src/stream_progress.cpp
   include/dak/utility/multi_thread_progress.h     src/multi_thread_progress.cpp
   include/dak/utility/stopwatch.h                 src/stopwatch.cpp
   include/dak/utility/thread_pool.h               src/thread_pool.cpp
   include/dak/utility/threaded_items_worker.h     src/threaded_items_worker.cpp
   include/dak/utility/threaded_worker.h
   include/dak/utility/selection.h
   include/dak/utility/text.h                      src/text.cpp
   include/dak/utility/type_info.h                 src/type_info.cpp
   include/dak/utility/types.h
   include/dak/utility/undo_stack.h                src/undo_stack.cpp
   include/dak/utility/work_item.h
)

target_include_directories(dak_utility PUBLIC
   include
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_utility PROPERTY CXX_STANDARD 20)

