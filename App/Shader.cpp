#include "Shader.h"

Shader::Shader(const std::string& filename) : m_filepath(filename), m_rendererID(0) {
    ShaderProgramSource source = ParseShader(filename);
    m_rendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

uint Shader::GetRendererID() const { return m_rendererID; }

Shader::~Shader() { glDeleteProgram(m_rendererID); }

ShaderProgramSource Shader::ParseShader(const std::string &filepath) {
    std::ifstream stream(filepath);
    std::string line;
    enum ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}
unsigned int Shader::CompileShader(const std::string &source, uint type) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vxShader = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fsShader = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
    glAttachShader(program, vxShader);
    glAttachShader(program, fsShader);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vxShader);
    glDeleteShader(fsShader);

    return program;
}
void Shader::Bind() {
    glUseProgram(m_rendererID);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL shader error occurred: " << error << std::endl;
    }
}

void Shader::Unbind() { glUseProgram(0); }

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}


void Shader::SetUniform3f(const std::string &name, const glm::vec3 &vec) {
    glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
}

void Shader::SetUniform1i(const std::string &name, int num) { glUniform1i(GetUniformLocation(name), num); }

void Shader::SetUniform1f(const std::string &name, float num) { glUniform1f(GetUniformLocation(name), num); }

int Shader::GetUniformLocation(const std::string &name) {
    if (m_UniformLocationCashe.find(name) != m_UniformLocationCashe.end()) return m_UniformLocationCashe[name];
    int location = glGetUniformLocation(m_rendererID, name.c_str());
    if (location == -1) {
        std::cout << "Warning:" << name << std::endl;
    }

    m_UniformLocationCashe[name] = location;
    return location;
}