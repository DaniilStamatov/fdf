#include "vbo.h"

VBO::VBO(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &m_vbo);
}

void VBO::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void VBO::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}