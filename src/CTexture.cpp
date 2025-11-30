#include "CTexture.h"

Texture::Texture()
{
    GLCALL( glGenTextures( 1, &m_TextureId ) );
    // GLCALL( glBindTexture( GL_TEXTURE_2D, m_TextureId ) );

    GLCALL( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ) );	
    GLCALL( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT ) );
    GLCALL( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR ) );
    GLCALL( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ) );
};

Texture::~Texture()
{
    GLCALL( glDeleteTextures( 1, &m_TextureId ) );
};

void Texture::bind( unsigned int slot ) const
{
    GLCALL( glActiveTexture( GL_TEXTURE0 + slot ) );
    GLCALL( glBindTexture( GL_TEXTURE_2D, m_TextureId ) );
};

void Texture::unbind() const
{
    GLCALL( glBindTexture( GL_TEXTURE_2D, 0 ) );
}
unsigned int Texture::get_id() const
{
    return m_TextureId;
};
