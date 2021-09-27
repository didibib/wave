# Collect files
set(SANDBOX_PCH_H
    "pch/sandboxpch.h"
)
set(SANDBOX_PCH_CPP
    "pch/sandboxpch.cpp"
)

set(SANDBOX_SOURCE_LIST
    "app.h"
    "app.cpp"
    "main.cpp"
    ${SANDBOX_PCH_H}
    ${SANDBOX_PCH_CPP}
)

add_executable(sandbox
    ${SANDBOX_SOURCE_LIST}
)

# Group sources according to the folder structure
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SANDBOX_SOURCE_LIST})

# Set output directories
set_target_output_directories(sandbox)

# Set precompiled headers
set_target_precompiled_header(sandbox SANDBOX_PCH_H SANDBOX_PCH_CPP)

target_include_directories(sandbox 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

set(FREE_IMAGE_DEST $<TARGET_FILE_DIR:sandbox>/FreeImage.dll)
# Copy the FreeImage.dll to the executable
add_custom_command(TARGET sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${FREE_IMAGE_DLL}
    ${FREE_IMAGE_DEST}
    COMMENT "Copying 'FreeImage.dll' from '${FREE_IMAGE_DLL}' to '${FREE_IMAGE_DEST}'"
)  