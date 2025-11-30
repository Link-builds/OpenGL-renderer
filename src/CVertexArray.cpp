#include <glad.h>

#include "CRenderer.h"
#include "CVertexArray.h"

VertexArray::VertexArray()
{
    GLCALL( glGenVertexArrays( 1, &m_VaID ) );
    GLCALL( glBindVertexArray( m_VaID ) );
};

VertexArray::~VertexArray()
{
    GLCALL( glDeleteVertexArrays( 1, &m_VaID ) );
};

void VertexArray::bind() const
{
    GLCALL( glBindVertexArray( m_VaID ) );
};

void VertexArray::unbind() const
{
    GLCALL( glBindVertexArray( 0 ) );
};

void VertexArray::add_buffer( const VertexBuffer &vbo, const VertexBufferLayout &layout )
{
    // bind();
    // vbo.bind();

    const auto  &elements = layout.get_elements();
    unsigned int offset = 0;

    for( unsigned int i = 0; i < elements.size(); i++ )
    {
        // std::cout << layout.get_stride() << " CURR STRIDE" << std::endl;
        // std::cout << offset << " CURR OFFSET" << std::endl;

        const auto &element = elements[i];

        GLCALL( glEnableVertexAttribArray( i ) );
        GLCALL( glVertexAttribPointer( i, element.count, element.type, element.normalized, layout.get_stride(), reinterpret_cast<const void *>(offset) ) );

        offset += element.count * VertexBufferElement::get_size( element.type );
    };
};