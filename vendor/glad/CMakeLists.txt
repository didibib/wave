set(GLAD_SRC "src/glad.c")

source_group("src" FILES ${GLAD_SRC})

add_library(glad STATIC 
    ${GLAD_SRC}
)

target_include_directories(glad 
    PUBLIC include
)