
set(SOURCES
    main.cpp
    Shader.cpp
    vao.cpp
    vbo.cpp
    map.cpp
    vboLayout.cpp
)
add_executable(FDF ${SOURCES})

# Связываем зависимости
target_link_libraries(FDF PRIVATE glfw glad OpenGL::GL glm) 