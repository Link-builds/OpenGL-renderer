#pragma once

class VertexBuffer
{
private:
    unsigned int m_RendererId;

public:
    VertexBuffer( const void *data, int size );

    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};