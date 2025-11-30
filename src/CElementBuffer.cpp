#include "CElementBuffer.h"
#include <glad.h>
#include "CRenderer.h"

ElementBuffer::ElementBuffer( const unsigned int *data, unsigned int count ) : m_Count( count )
{
    GLCALL( glGenBuffers( 1, &m_RendererId ) );
    GLCALL( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_RendererId ) );
    GLCALL( glBufferData( GL_ELEMENT_ARRAY_BUFFER, count * sizeof( unsigned int ), data, GL_STATIC_DRAW ) );
};

ElementBuffer::~ElementBuffer()
{
    GLCALL( glDeleteBuffers( 1, &m_RendererId ) );
};

void ElementBuffer::bind() const
{
    GLCALL( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_RendererId ) );
};

void ElementBuffer::unbind() const
{
    GLCALL( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ) );
};