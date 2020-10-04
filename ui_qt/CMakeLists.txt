# Qt 5 stuff

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS WinExtras REQUIRED)

add_library(ui_qt
   include/dak/ui/qt/canvas.h                         src/canvas.cpp
   include/dak/ui/qt/convert.h                        src/convert.cpp
   include/dak/ui/qt/double_editor.h                  src/double_editor.cpp
   include/dak/ui/qt/drawing_canvas.h                 src/drawing_canvas.cpp
   include/dak/ui/qt/edges_map_canvas.h               src/edges_map_canvas.cpp
   include/dak/ui/qt/function_drawing_canvas.h
   include/dak/ui/qt/int_editor.h                     src/int_editor.cpp
   include/dak/ui/qt/layered_canvas.h                 src/layered_canvas.cpp
   include/dak/ui/qt/message_reporter.h               src/message_reporter.cpp
   include/dak/ui/qt/paint_device_drawing.h           src/paint_device_drawing.cpp
   include/dak/ui/qt/paint_device_transformable.h     src/paint_device_transformable.cpp
   include/dak/ui/qt/painter_drawing.h                src/painter_drawing.cpp
   include/dak/ui/qt/painter_transformable.h          src/painter_transformable.cpp
   include/dak/ui/qt/qt_drawing_base.h                src/qt_drawing_base.cpp
   include/dak/ui/qt/widget_mouse_emitter.h           src/widget_mouse_emitter.cpp
)

target_include_directories(ui_qt PUBLIC
   include
   "${CMAKE_CURRENT_SOURCE_DIR}/../utility/include"
   "${CMAKE_CURRENT_SOURCE_DIR}/../geometry/include"
   "${CMAKE_CURRENT_SOURCE_DIR}/../ui/include"
)

target_include_directories(ui_qt PUBLIC
   "${Qt5Core_INCLUDE_DIRS}"
   "${Qt5Widgets_INCLUDE_DIRS}"
   "${Qt5Gui_INCLUDE_DIRS}"
   "${Qt5WinExtras_INCLUDE_DIRS}"
)

target_compile_features(ui_qt PUBLIC
   cxx_std_20
)

