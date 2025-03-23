#include "vao.h"

VAO::VAO()
{
    glGenVertexArrays(1, &m_vao);
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &m_vao);
}

void VAO::Bind() const
{
    glBindVertexArray(m_vao);
}

void VAO::Unbind() const
{
    glBindVertexArray(0);
}

void VAO::AddBuffer(const VBO &vbo, const VBOLayout &layout)
{
    Bind();
    vbo.Bind();
    const auto& elems = layout.GetElements();
    unsigned int offset = 0;
    for(size_t i = 0; i < elems.size(); i++) {
        const auto& element  = elems[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.GetSizeOfType(element.type), element.normalized, layout.GetStride(), (const void*)offset);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}
