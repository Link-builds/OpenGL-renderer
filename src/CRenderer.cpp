#include "CRenderer.h"

void gl_clear_error()
{
    while( glGetError() != GL_NO_ERROR );
};

bool gl_log_call( const char *function, const char *file, int line )
{
    while( GLenum err = glGetError() )
    {
        std::cout << "[OpenGL Error] ( " << err << " ): " << function << std::endl << "In file: " << file << " Line: " << line
        << std::endl;
        return false;
    };

    return true;
};

void Renderer::draw( const VertexArray &vao, const ElementBuffer &ebo, const Shader &shader ) const
{
    shader.bind();
    vao.bind();
    ebo.bind();
    
    GLCALL( glDrawElements( GL_TRIANGLES, ebo.get_count(), GL_UNSIGNED_INT, nullptr ) );
};

void Renderer::clear() const
{
    GLCALL( glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) );
};

void Renderer::set_background_color(float r, float g, float b, float a)
{
    GLCALL( glClearColor( r, g, b, a ) );
};

void Renderer::set_background_color( ImVec4 rgba )
{
    GLCALL( glClearColor( rgba.x, rgba.y, rgba.z, rgba.w ) );
};