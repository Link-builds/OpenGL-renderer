#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace funs
{

// Simple program exit funciton
void handle_err( std::string message );

// For second argument of glfwSetFramebufferSizeCallback()
void framebufferSize_Callback( GLFWwindow *window, int width, int height );

// Simple keyboard input processor
void process_inputs( GLFWwindow *window );

// Render window setup for OpenGL core profile
void setup_render_window_CORE( int majorVersion, int minorVersion );

void create_my_shader( unsigned int &shader, int shaderType, const char *source );

void create_my_shader_program( unsigned int &shaderProgram, unsigned int &shader1, unsigned int &shader2 );

GLFWwindow * setup_viewport( const std::string &windowName, int width, int height ,int vSync );

};
