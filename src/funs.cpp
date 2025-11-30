#include <iostream>
#include <glad.h>
#include <imgui/imgui.h>
#include <imgui/imconfig.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <string>

#include "funs.h"



#define IMGUI_SET 0

// Simple program exit funciton
void funs::handle_err( std::string message )
{
    // std::cerr << message << std::endl;
    glfwTerminate();
    throw std::runtime_error( message );
};

// For second argument of glfwSetFramebufferSizeCallback()
void funs::framebufferSize_Callback( GLFWwindow *window, int width, int height )
{
    glViewport( 0, 0, width, height );

#if IMGUI_SET

// TODO: Scale ImGui windows with resize of render window

#endif

};

// Simple keyboard input processor
void funs::process_inputs( GLFWwindow *window )
{
    if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
        glfwSetWindowShouldClose( window, 1 );

    if( glfwGetKey( window, GLFW_KEY_P ) == GLFW_PRESS )
        glad_glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );

    if( glfwGetKey( window, GLFW_KEY_P ) == GLFW_RELEASE )
        glad_glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
};

// Render window setup for OpenGL core profile
void funs::setup_render_window_CORE( int majorVersion, int minorVersion )
{
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, majorVersion );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, minorVersion );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
};

void funs::create_my_shader( unsigned int &shader, int shaderType, const char *source )
{
    shader = glCreateShader( shaderType );
    glShaderSource( shader, 1, &source, NULL );
    glCompileShader( shader );

    // Vertex shader compilation error check
    int  success;
    char infoLog[512];
    glGetShaderiv( shader, GL_COMPILE_STATUS, &success );

    if( !success )
    {
        glGetShaderInfoLog( shader, 512, NULL, infoLog );
        std::cout << infoLog << std::endl;
        handle_err( "ERR: Failed to compile " + shaderType );
    };
};

void funs::create_my_shader_program( unsigned int &shaderProgram, unsigned int &shader1, unsigned int &shader2 )
{
    shaderProgram = glCreateProgram();

    // Attach and link created shaders to program
    glAttachShader( shaderProgram, shader1 );
    glAttachShader( shaderProgram, shader2 );
    glLinkProgram( shaderProgram );

    // Shader program linking error check
    int  successP;
    char infoLogP[512];
    glGetProgramiv( shaderProgram, GL_LINK_STATUS, &successP );

    if( !successP )
    {
        glGetProgramInfoLog( shaderProgram, 512, NULL, infoLogP );
        std::cout << infoLogP << std::endl;
        handle_err( "ERR: Failed to link shaders" );
    };
    
    // Beacuse shaders are now linked to program, delete them
    glDeleteShader( shader1 );
    glDeleteShader( shader2 );
}

GLFWwindow *funs::setup_viewport( const std::string &windowName, int width, int height ,int vSync )
{
    // glfw: initialize and configure
    if( !glfwInit() ) funs::handle_err( "ERR: Failed to initialize GLFW!" );

    funs::setup_render_window_CORE( 3, 3 );

    // glfw window creation
    GLFWwindow *window = glfwCreateWindow( width, height, windowName.c_str(), NULL, NULL );
    if( window == NULL ) funs::handle_err( "ERR: Failed to create window!" );

    glfwMakeContextCurrent( window );
    glfwSetFramebufferSizeCallback( window, funs::framebufferSize_Callback );
    glfwSwapInterval( vSync ); // Enable vsync

    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    if( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
    {
        funs::handle_err( "ERR: Failed to initialize GLAD" );
    }

    glEnable( GL_DEPTH_TEST );

    return window;
}
