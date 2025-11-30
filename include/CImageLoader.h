#pragma once

#include <glad.h>
#include <iostream>
#include <stb_image.h>
#include <string>

#include "funs.h"
#include "CTexture.h"

class ImageLoader
{
private:
    int m_Width;
    int m_Height;
    int m_NumOfChannels;
    const std::string m_DataPath;
    unsigned char *m_Data;
public:
    ImageLoader( const std::string &path );

    ~ImageLoader() { stbi_image_free( m_Data ); };

    void print_image_info() const;
    void generate_texture_from_image( const Texture &tex ) const;
};