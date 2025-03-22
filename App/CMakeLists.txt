add_executable(App main.cpp)

# Связываем зависимости
target_link_libraries(App PRIVATE glfw glad OpenGL::GL glm)