# Collect core files
set(WAVE_PCH_H        
    "include/wavepch.h"
)
set(WAVE_PCH_CPP      
    "src/wavepch.cpp"
)
set(WAVE_UTIL  
    "include/util.h"
)
set(WAVE_H 
    "include/wave.h"
)
set(WAVE_WINDOW
    "include/window.h"
    "include/window_glfw.h"
    "src/window_glfw.cpp"
)
set(WAVE_INPUT
    "include/input.h"
    "src/input.cpp"
)
set(WAVE_LOG
    "include/log.h"
    "src/log.cpp"
)
set(WAVE_IMGUI_CONTEXT
    "include/imgui_context.h"
    "src/imgui_context.cpp"
)
set(WAVE_SHADER
    "include/shader.h"
    "src/shader.cpp"
)
set(WAVE_BUFFERS
    "include/opengl_buffers.h"
    "src/opengl_buffers.cpp"
)
set(WAVE_TEXTURE
    "include/opengl_texture.h"
    "src/opengl_texture.cpp"
)
set(WAVE_CAMERA
    "include/camera.h"
    "src/camera.cpp"
)
# Set filters
source_group("include" FILES
    ${WAVE_H}
)
source_group("pch" FILES 
    ${WAVE_PCH_H} 
    ${WAVE_PCH_CPP} 
)
source_group("util" FILES
    ${WAVE_SUBDEC}
    ${WAVE_LOG}
)
source_group("window" FILES
    ${WAVE_WINDOW}
)
source_group("input" FILES
    ${WAVE_INPUT}
)
source_group("context" FILES
    ${WAVE_IMGUI_CONTEXT}
)
source_group("shader" FILES
    ${WAVE_SHADER}
)
source_group("buffers" FILES
    ${WAVE_BUFFERS}
)
source_group("texture" FILES
    ${WAVE_TEXTURE}
)
source_group("camera" FILES 
    ${WAVE_CAMERA}
)

# Build static library
add_library(wave STATIC
    ${WAVE_PCH_H} ${WAVE_PCH_CPP}   
    ${WAVE_SUBDEC}
    ${WAVE_H}
    ${WAVE_WINDOW}
    ${WAVE_INPUT} 
    ${WAVE_LOG}
    ${WAVE_IMGUI_CONTEXT}
    ${WAVE_SHADER}
    ${WAVE_BUFFERS}
    ${WAVE_TEXTURE}
    ${WAVE_CAMERA}
)

# Set output directories    
set_target_output_directories(wave)

# Set precompiled headers
set_target_precompiled_header(wave "wavepch.h" "wavepch.cpp" WAVE_PCH_CPP)

# Specify include directories
target_include_directories(wave 
    PUBLIC include
    PUBLIC ${FREE_IMAGE_INCLUDE}
)

# Find OpenGL
find_package(OpenGL)

# Link libraries to wave
target_link_libraries(wave PUBLIC
    ${OPENGL_gl_LIBRARY}
    glad
    glfw
    glm
    spdlog::spdlog
    imgui
    ${FREE_IMAGE_LIB}
)