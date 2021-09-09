# Set PCH for VS project
function(set_target_precompiled_header target headerFile sourceFile sourcePath)
    if(MSVC)
        message(STATUS "Setting precompiled headers for: '${target}'")
        set_target_properties(${target} 
            PROPERTIES 
                COMPILE_OPTIONS "/Yu${headerFile}"
        )
        set_source_files_properties(${${sourcePath}}
            PROPERTIES 
                COMPILE_OPTIONS "/Yc${headerFile}"
        )
    endif(MSVC)
endfunction(set_target_precompiled_header)


