#include "CImageLoader.h"

ImageLoader::ImageLoader( const std::string &path ) : m_DataPath( path )
{
    stbi_set_flip_vertically_on_load( 1 );
    m_Data = stbi_load( m_DataPath.c_str(), &m_Width, &m_Height, &m_NumOfChannels, STBI_rgb_alpha );

    if( !m_Data ) funs::handle_err( "ERR: Failed to load image data" );
};

void ImageLoader::print_image_info() const
{
    std::cout << "File (channels = " << m_NumOfChannels << ')'<< ": " << m_DataPath 
    << std::endl << m_Width << 'x' << m_Height << std::endl;
}

void ImageLoader::generate_texture_from_image( const Texture &tex ) const
{
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data );

    glGenerateMipmap( GL_TEXTURE_2D );
};