
add_library(dak_ui
   include/dak/ui/color.h              src/color.cpp
   include/dak/ui/drawing.h
   include/dak/ui/drawing_base.h       src/drawing_base.cpp
   include/dak/ui/edges_map_layer.h    src/edges_map_layer.cpp
   include/dak/ui/dxf_drawing.h        src/dxf_drawing.cpp
   include/dak/ui/eps_drawing.h        src/eps_drawing.cpp
   include/dak/ui/layer.h              src/layer.cpp
   include/dak/ui/layered.h            src/layered.cpp
   include/dak/ui/modifiers.h
   include/dak/ui/mouse.h              src/mouse.cpp
   include/dak/ui/stroke.h
   include/dak/ui/transformable.h
   include/dak/ui/transformer.h        src/transformer.cpp
)

target_include_directories(dak_ui PUBLIC
   include
)

target_link_libraries(dak_ui dak_geometry)
target_link_libraries(dak_ui dak_utility)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET dak_ui PROPERTY CXX_STANDARD 20)

