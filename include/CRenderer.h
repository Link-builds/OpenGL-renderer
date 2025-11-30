#pragma once

#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

#include "CVertexArray.h"
#include "CElementBuffer.h"
#include "CShader.h"

#define ASSERT(x) if (!(x)) exit( EXIT_FAILURE );
#define GLCALL(x) gl_clear_error();\
    x;\
    ASSERT( gl_log_call( #x, __FILE__, __LINE__ ) )

void gl_clear_error();

bool gl_log_call( const char *function, const char *file, int line );

class Renderer
{
private:

public:
    void draw( const VertexArray &vao, const ElementBuffer &ebo, const Shader &shader ) const;
    void clear() const;
    void set_background_color( float r, float g, float b, float a );
    void set_background_color( ImVec4 rgba );
};