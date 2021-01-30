
add_library(ui
   include/dak/ui/color.h              src/color.cpp
   include/dak/ui/drawing.h
   include/dak/ui/drawing_base.h       src/drawing_base.cpp
   include/dak/ui/edges_map_layer.h    src/edges_map_layer.cpp
   include/dak/ui/eps_drawing.h        src/eps_drawing.cpp
   include/dak/ui/layer.h              src/layer.cpp
   include/dak/ui/layered.h            src/layered.cpp
   include/dak/ui/modifiers.h
   include/dak/ui/mouse.h              src/mouse.cpp
   include/dak/ui/stroke.h
   include/dak/ui/transformable.h
   include/dak/ui/transformer.h        src/transformer.cpp
)

target_include_directories(ui PUBLIC
   include
   "${CMAKE_CURRENT_SOURCE_DIR}/../utility/include"
   "${CMAKE_CURRENT_SOURCE_DIR}/../geometry/include"
)

set_property(TARGET ui PROPERTY CXX_STANDARD 20)

