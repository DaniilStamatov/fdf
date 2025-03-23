#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "map.h"
#include "vao.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main () {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "fdf", nullptr, nullptr);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
   
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Map map("/home/daniil/Documents/fdf/App/res/maps/3map.txt");
    std::vector<glm::vec3> vertices = map.GetPoints();
    std::vector<glm::vec3> lines;
    int width = map.GetWidth();
    int height = map.GetHeight();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x < width - 1) {
                lines.push_back(vertices[y * width + x]); 
                lines.push_back(vertices[y * width + (x + 1)]);
            }
            if (y < height - 1) {
                lines.push_back(vertices[y * width + x]);
                lines.push_back(vertices[(y + 1) * width + x]); 
            }
        }
    }
    uint32_t m_vbo;
    uint32_t m_vao;
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(glm::vec3), lines.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    Shader shader("/home/daniil/Documents/fdf/App/res/shaders/basic.shader");
    shader.Unbind();
     glm::vec3 translation(1, 0, 0);
     int max = map.GetMaxHeight();
    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        processInput(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glm::mat4 proj = glm::perspective(glm::radians(camera.GetZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f)); 

        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));   
        shader.Bind();
        shader.SetUniformMat4f("u_projection", proj);
        shader.SetUniformMat4f("u_view", view);
        shader.SetUniformMat4f("u_model", model);
        shader.SetUniform1f("u_MaxY", max);
        glBindVertexArray(m_vao);
        glDrawArrays(GL_LINES, 0, lines.size());
        glfwSwapBuffers(window);
        
        glfwPollEvents();    
    }
}