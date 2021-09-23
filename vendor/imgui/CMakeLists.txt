set(IMGUI_SRC
    "imconfig.h"
    "imgui.h"
    "imgui_internal.h"
    "imstb_rectpack.h"
    "imstb_textedit.h"
    "imstb_truetype.h"
    "imgui.cpp"
    "imgui_demo.cpp"
    "imgui_draw.cpp"
    "imgui_tables.cpp"
    "imgui_widgets.cpp"    
)

set(IMGUI_BACKENDS
    "backends/imgui_impl_opengl3.h"
    "backends/imgui_impl_opengl3.cpp"
    "backends/imgui_impl_glfw.h"
    "backends/imgui_impl_glfw.cpp"
)

source_group("src" FILES ${IMGUI_SRC})
source_group("backends" FILES ${IMGUI_BACKENDS})

add_library(imgui STATIC
    ${IMGUI_SRC}
    ${IMGUI_BACKENDS}
)

target_compile_definitions(imgui
    PRIVATE 
        IMGUI_IMPL_OPENGL_LOADER_GLAD=1
)

target_include_directories(imgui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${VENDOR_DIR}/glfw/include
    PRIVATE ${VENDOR_DIR}/glad/include
)