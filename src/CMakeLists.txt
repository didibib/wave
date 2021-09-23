# Collect files
set(WAVE_PCH_H
    "pch/wavepch.h"
)

set(WAVE_PCH_CPP
    "pch/wavepch.cpp"
)

set(WAVE_SOURCE_LIST
    "asset/shader/shader.h"
    "asset/shader/shader.cpp"
    "asset/shader/shader_manager.h"
    "asset/shader/shader_manager.cpp"
    "asset/texture/texture.h"
    "asset/texture/texture_manager.h"
    "asset/texture/texture_manager.cpp"    
    "buffer/vertex_buffer.h"
    "buffer/vertex_buffer.cpp"    
    "imgui/imgui_context.h"
    "imgui/imgui_context.cpp"    
    "entity/camera/camera.h"
    "entity/camera/camera.cpp"
    "entity/light/light.h"
    "entity/light/light.cpp"
    "entity/mesh/cube.h"
    "entity/object/object.h"
    "entity/object/object.cpp"
    "event/event.h"
    "event/event_handler.h"
    "event/event_handler.cpp"
    "include/wave.h"
    ${WAVE_PCH_H}
    ${WAVE_PCH_CPP}
    "util/log.h"
    "util/log.cpp"
    "util/util.h"
    "window/window.h"
    "window/window_glfw.h"
    "window/window_glfw.cpp"
)

# Build static library
add_library(wave STATIC
    ${WAVE_SOURCE_LIST}
)

# Group sources according to the folder structure
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${WAVE_SOURCE_LIST})

# Add macro specifying assets directory
# ${ASSETS_DRI} is set in the root 
target_compile_definitions(wave PRIVATE ASSETS_DIR=${ASSETS_DIR})

# Set output directories    
set_target_output_directories(wave)

# Set precompiled headers
set_target_precompiled_header(wave WAVE_PCH_H WAVE_PCH_CPP)

# Specify include directories
# Make them public so that executables can inherit them
target_include_directories(wave 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${FREE_IMAGE_INCLUDE}
)

# Find OpenGL
find_package(OpenGL)

# Link libraries to wave
# Make them public so that executables can inherit them
target_link_libraries(wave PUBLIC
    ${OPENGL_gl_LIBRARY}
    glad
    glfw
    glm
    spdlog::spdlog
    imgui
    ${FREE_IMAGE_LIB}
)