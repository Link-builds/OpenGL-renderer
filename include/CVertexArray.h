#pragma once

#include "CVertexBuffer.h"
#include "CVertexBufferLayout.h"

class VertexBufferLayout;

class VertexArray
{
private:
    unsigned int m_VaID;
        
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void add_buffer( const VertexBuffer &vbo, const VertexBufferLayout &layout );
};