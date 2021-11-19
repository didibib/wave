# Project name
set(EDITOR_TARGET_NAME "editor")

# Collect files
set(EDITOR_PCH_H "pch/editorpch.h")
set(EDITOR_PCH_CPP "pch/editorpch.cpp")

set(EDITOR_SOURCE_LIST
    ${EDITOR_PCH_H}
    ${EDITOR_PCH_CPP}
    "editor_app.h"
    "editor_app.cpp"
    "editor_main.cpp"
)

add_executable(${EDITOR_TARGET_NAME} ${EDITOR_SOURCE_LIST})

# Group sources according to the folder structure
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EDITOR_SOURCE_LIST})

# Set output directories
set_target_output_directories(${EDITOR_TARGET_NAME})

# Set precompiled headers
set_target_precompiled_header(${EDITOR_TARGET_NAME} EDITOR_PCH_H EDITOR_PCH_CPP)

target_include_directories(${EDITOR_TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set(FREE_IMAGE_DEST $<TARGET_FILE_DIR:${EDITOR_TARGET_NAME}>/FreeImage.dll)
# Copy the FreeImage.dll to the executable
add_custom_command(TARGET editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${FREE_IMAGE_DLL}
    ${FREE_IMAGE_DEST}
    COMMENT "Copying 'FreeImage.dll' from '${FREE_IMAGE_DLL}' to '${FREE_IMAGE_DEST}'"
)  