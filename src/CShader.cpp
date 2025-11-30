#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glad.h>
#include <GLFW/glfw3.h>

#include "CRenderer.h"
#include "CShader.h"
#include "funs.h"

Shader::Shader( const char *vertex_path, const char *fragment_path )
{
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream vShader_file;
    std::ifstream fShader_file;

    vShader_file.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    fShader_file.exceptions( std::ifstream::failbit | std::ifstream::badbit );

    try
    {
        vShader_file.open( vertex_path );
        fShader_file.open( fragment_path );
        std::stringstream vShader_stream, fShader_stream;

        vShader_stream << vShader_file.rdbuf();
        fShader_stream << fShader_file.rdbuf();

        vShader_file.close();
        fShader_file.close();

        vertex_code = vShader_stream.str();
        fragment_code = fShader_stream.str();
    }
    catch( std::ifstream::failure &e )
    {
        std::cerr << "ERR: Failed to load from file: " << e.what() << std::endl;
    };

    unsigned int vertex_shader;
    unsigned int fragment_shader;

    funs::create_my_shader( vertex_shader, GL_VERTEX_SHADER, vertex_code.c_str() );
    funs::create_my_shader( fragment_shader, GL_FRAGMENT_SHADER, fragment_code.c_str() );

    funs::create_my_shader_program( m_ShaderId, vertex_shader, fragment_shader );
};

Shader::~Shader()
{
    GLCALL( glDeleteProgram( m_ShaderId ) );
};

void Shader::bind() const
{
    GLCALL( glUseProgram( m_ShaderId ) );
};

void Shader::unbind() const
{
    GLCALL( glUseProgram( 0 ) );
};

void Shader::setBool( const std::string &name, bool value ) const
{
    glUniform1i( glGetUniformLocation( m_ShaderId, name.c_str() ), ( int )value );
};

void Shader::setInt( const std::string &name, int value ) const
{
    glUniform1i( glGetUniformLocation( m_ShaderId, name.c_str() ), value );
};

void Shader::setFloat( const std::string &name, float value ) const
{
    glUniform1f( glGetUniformLocation( m_ShaderId, name.c_str() ), value );
};

void Shader::setVec2( const std::string &name, const glm::vec2 &value ) const
{ 
    glUniform2fv( glGetUniformLocation( m_ShaderId, name.c_str() ), 1, &value[0] ); 
};

void Shader::setVec2( const std::string &name, float x, float y ) const
{ 
    glUniform2f( glGetUniformLocation( m_ShaderId, name.c_str() ), x, y ); 
};

void Shader::setVec3( const std::string &name, const glm::vec3 &value ) const
{ 
    glUniform3fv( glGetUniformLocation( m_ShaderId, name.c_str() ), 1, &value[0] ); 
};

void Shader::setVec3( const std::string &name, float x, float y, float z ) const
{ 
    glUniform3f( glGetUniformLocation( m_ShaderId, name.c_str() ), x, y, z ); 
};

void Shader::setVec4( const std::string &name, const glm::vec4 &value ) const
{ 
    glUniform4fv(glGetUniformLocation( m_ShaderId, name.c_str() ), 1, &value[0] ); 
};

void Shader::setVec4( const std::string &name, float x, float y, float z, float w ) const
{ 
    glUniform4f( glGetUniformLocation( m_ShaderId, name.c_str() ), x, y, z, w ); 
};

void Shader::setMat2( const std::string &name, const glm::mat2 &mat ) const
{
    glUniformMatrix2fv( glGetUniformLocation( m_ShaderId, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
};

void Shader::setMat3( const std::string &name, const glm::mat3 &mat ) const
{
    glUniformMatrix3fv( glGetUniformLocation( m_ShaderId, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
};

void Shader::setMat4( const std::string &name, const glm::mat4 &mat ) const
{
    glUniformMatrix4fv( glGetUniformLocation( m_ShaderId, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
};