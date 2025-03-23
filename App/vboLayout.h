#pragma once
#include <glad/gl.h>
#include <vector>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:         return 4;
        case GL_UNSIGNED_INT:  return 4;
        case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
    }
};

class VBOLayout {
public:
    VBOLayout() : m_stride(0) {}

    void Push(unsigned int count) {
        m_elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    std::vector<VertexBufferElement> GetElements() const { return m_elements; }
    
    unsigned int GetStride() const { return m_stride; }

private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;
};
