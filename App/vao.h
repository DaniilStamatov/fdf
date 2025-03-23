
#pragma once
#include "vbo.h"

class VAO{
public:
    VAO();
    ~VAO();
    void Bind() const;
    void Unbind() const;
    void AddBuffer(const VBO& vbo, const VBOLayout& layout);
private:
    uint32_t m_vao;
};