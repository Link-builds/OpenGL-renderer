#pragma once

#include <vector>
#include <cassert>
#include "CRenderer.h"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    int normalized;

    VertexBufferElement( unsigned int t, unsigned int c,  int n ) : type(t), count(c), normalized(n) {};

    static unsigned int get_size( unsigned int type )
    {
        switch( type )
        {
            case GL_FLOAT: return 4; 
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        };

        return 0;
    };
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride = 0;
public:
    VertexBufferLayout() {};

    template<typename T>
    void push( unsigned int count ) { static_assert( false ); };

    unsigned int get_stride() const { return m_Stride; };
    const std::vector<VertexBufferElement> & get_elements() const { return m_Elements; };
};

template<>
inline void VertexBufferLayout::push<float>( unsigned int count )
{
    m_Elements.push_back( VertexBufferElement( {GL_FLOAT, count, GL_FALSE} ) );
    m_Stride += VertexBufferElement::get_size( GL_FLOAT ) * count;
};

template<>
inline void VertexBufferLayout::push<unsigned int>( unsigned int count )
{
    m_Elements.push_back( VertexBufferElement( {GL_UNSIGNED_INT, count, GL_FALSE} ) );
    m_Stride += VertexBufferElement::get_size( GL_UNSIGNED_INT ) * count;
};

template<>
inline void VertexBufferLayout::push<unsigned char>( unsigned int count )
{
    m_Elements.push_back( VertexBufferElement( {GL_UNSIGNED_BYTE, count, GL_TRUE} ) );
    m_Stride += VertexBufferElement::get_size( GL_UNSIGNED_BYTE ) * count;
};