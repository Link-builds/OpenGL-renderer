#include "CVertexBuffer.h"
#include <glad.h>
#include "CRenderer.h"

VertexBuffer::VertexBuffer( const void *data, int size )
{
    GLCALL( glGenBuffers( 1, &m_RendererId ) );
    GLCALL( glBindBuffer( GL_ARRAY_BUFFER, m_RendererId ) );
    GLCALL( glBufferData( GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW ) );
};

VertexBuffer::~VertexBuffer()
{
    GLCALL( glDeleteBuffers( 1, &m_RendererId ) );
};

void VertexBuffer::bind() const
{
    GLCALL( glBindBuffer( GL_ARRAY_BUFFER, m_RendererId ) );
};

void VertexBuffer::unbind() const
{
    GLCALL( glBindBuffer( GL_ARRAY_BUFFER, 0 ) );
};