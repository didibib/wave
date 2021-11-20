# Project name
set(WAVE_TARGET_NAME "wave")

# Collect files
set(WAVE_PCH_H "pch/wavepch.h")
set(WAVE_PCH_CPP "pch/wavepch.cpp")

set(WAVE_SOURCE_LIST
    "app/app.h"
    "event/event.h"
    "event/event_handler.h"
    "event/event_handler.cpp"       
    "imgui/imgui_context.h"
    "imgui/imgui_context.cpp"
    "include/wave.h"
    ${WAVE_PCH_H}
    ${WAVE_PCH_CPP}    
    "scene/camera/camera.h"
    "scene/camera/camera.cpp"
    "scene/light/light.h"
    "scene/light/light.cpp"
    "scene/mesh/cube.h"
    "scene/mesh/mesh.h"
    "scene/mesh/mesh.cpp"
    "scene/mesh/vertex.h"
    "scene/mesh/vertex_buffer.h"
    "scene/mesh/vertex_buffer.cpp"   
    "scene/model/model.h"
    "scene/model/model.cpp"
    "scene/object/object.h"
    "scene/object/object.cpp" 
    "scene/shader/shader.h"
    "scene/shader/shader.cpp"
    "scene/texture/texture.h"
    "scene/texture/texture_manager.h"
    "scene/texture/texture_manager.cpp" 
    "util/logger/logger.h"
    "util/logger/logger.cpp"
    "util/locator/locator.h"
    "util/result.h"
    "util/util.h"
    "window/window.h"
    "window/window.cpp"
    "window/window_params.h"
    "engine.h"
    "engine.cpp"
    "subsystem.h"
)

# Build static library
add_library(${WAVE_TARGET_NAME} STATIC ${WAVE_SOURCE_LIST})

# Group sources according to the folder structure
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${WAVE_SOURCE_LIST})

# Add macro specifying assets directory
# ${ASSETS_DIR} is set in the root 
target_compile_definitions(${WAVE_TARGET_NAME} PUBLIC 
    WAVE_ASSETS_DIR=${WAVE_ASSETS_DIR}
    IMGUI_IMPL_OPENGL_LOADER_GLAD=1
)

# Set output directories    
set_target_output_directories(${WAVE_TARGET_NAME})

# Set precompiled headers
set_target_precompiled_header(${WAVE_TARGET_NAME} WAVE_PCH_H WAVE_PCH_CPP)

# Specify include directories
# Make them public so that executables can inherit them
target_include_directories(${WAVE_TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FREE_IMAGE_INCLUDE}
    "${WAVE_VENDOR_DIR}/imgui"
)

# Find OpenGL
find_package(OpenGL)

# Link libraries to wave
# Make them public so that executables can inherit them
target_link_libraries(${WAVE_TARGET_NAME} PUBLIC
    ${OPENGL_gl_LIBRARY}
    glad
    glfw
    glm
    spdlog::spdlog
    ${FREE_IMAGE_LIB}
    assimp
)