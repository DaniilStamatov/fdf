#pragma once
#include <glad/gl.h>
#include "vboLayout.h"
class VBO {
    public:
    VBO(const void* data, unsigned int size);
    ~VBO();

    void Bind() const;
    void Unbind() const;
    private:
    unsigned int m_vbo;
};