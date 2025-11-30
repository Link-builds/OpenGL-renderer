#pragma once

#include "CRenderer.h"

class Texture
{
private:
    unsigned int m_TextureId;

public:
    Texture();

    ~Texture();

    void bind( unsigned int slot = 0 ) const;
    void unbind() const;

    unsigned int get_id() const;
};