#pragma once

class ElementBuffer
{
private:
    unsigned int m_RendererId;
    unsigned int m_Count;

public:
    ElementBuffer( const unsigned int *data, unsigned int count );

    ~ElementBuffer();

    void bind() const;
    void unbind() const;

    const unsigned int get_count() const { return m_Count; };
};