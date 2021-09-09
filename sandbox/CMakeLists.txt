set(SANDBOX_MAIN
    "src/main.cpp"
)

set(SANDBOX_APP
    "include/app.h"
    "src/app.cpp"
)

set(SANDBOX_PCH_H "include/sandboxpch.h")
set(SANDBOX_PCH_CPP "src/sandboxpch.cpp")

source_group("main" FILES ${SANDBOX_MAIN})
source_group("app"  FILES ${SANDBOX_APP})
source_group("pch"  FILES ${SANDBOX_PCH_H} ${SANDBOX_PCH_CPP})

add_executable(sandbox
    ${SANDBOX_MAIN}
    ${SANDBOX_APP}
    ${SANDBOX_PCH_H} ${SANDBOX_PCH_CPP}
)

# Set output directories
set_target_output_directories(sandbox)

# Set precompiled headers
set_target_precompiled_header(sandbox "sandboxpch.h" "sandboxpch.cpp" SANDBOX_PCH_CPP)

target_include_directories(sandbox 
    PRIVATE include
)

set(SANDBOX_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
set(SANDBOX_ASSETS_DEST $<TARGET_FILE_DIR:sandbox>/assets)
# Copy the assets folder to the executable folder
add_custom_command(TARGET sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SANDBOX_ASSETS_DIR}
    ${SANDBOX_ASSETS_DEST}
    COMMENT "Copying assets from ${SANDBOX_ASSETS_DIR} to ${SANDBOX_ASSETS_DEST}"
)

set(FREE_IMAGE_DEST $<TARGET_FILE_DIR:sandbox>/FreeImage.dll)
# Copy the FreeImage.dll to the executable
add_custom_command(TARGET sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${FREE_IMAGE_DLL}
    ${FREE_IMAGE_DEST}
    COMMENT "Copying 'FreeImage.dll' from '${FREE_IMAGE_DLL}' to '${FREE_IMAGE_DEST}'"
)  