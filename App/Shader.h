#pragma once

#include <glad/gl.h>
#include <string>
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};
class Shader {
   public:
    Shader(const std::string &filename);
    void Bind();
    void Unbind();
    void SetUniformMat4f(const std::string &name, const glm::mat4 &mat);
    void SetUniform3f(const std::string &name, const glm::vec3 &vector);
    void SetUniform1i(const std::string &name, int num);
    void SetUniform1f(const std::string &name, float num);

    uint GetRendererID() const;
    ~Shader();

   private:
    ShaderProgramSource ParseShader(const std::string &filename);
    uint CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    uint CompileShader(const std::string &source, uint type);
    int GetUniformLocation(const std::string &name);
    uint m_rendererID;
    std::unordered_map<std::string, int> m_UniformLocationCashe;
    std::string m_filepath;
};