# Qt 5 stuff

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS WinExtras REQUIRED)

add_library(dak_ui_qt
   include/dak/ui/qt/canvas.h                         src/canvas.cpp
   include/dak/ui/qt/convert.h                        src/convert.cpp
   include/dak/ui/qt/color_editor.h                   src/color_editor.cpp
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

target_include_directories(dak_ui_qt PUBLIC
   include
)

target_link_libraries(dak_ui_qt dak_geometry)
target_link_libraries(dak_ui_qt dak_utility)
target_link_libraries(dak_ui_qt dak_ui)
target_link_libraries(dak_ui_qt Qt5::Core Qt5::Widgets Qt5::Gui Qt5::WinExtras)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_ui_qt PROPERTY CXX_STANDARD 20)

