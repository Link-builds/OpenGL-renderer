#pragma once

#include <glad.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imconfig.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "funs.h"
#include "CShader.h"
#include "CRenderer.h"
#include "CVertexBuffer.h"
#include "CElementBuffer.h"
#include "CVertexArray.h"
#include "CImageLoader.h"
#include "CCamera.h"

#define IMGUI_SET 1

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;


class Application
{
private:
    GLFWwindow *m_window;

    std::vector<float> m_vertices;
    // std::vector<float> m_indices;

    VertexBuffer *m_VBO = nullptr;
    VertexArray *m_VAO = nullptr;
    // ElementBuffer *m_EBO = nullptr;
    VertexBufferLayout m_layout;
    Renderer m_renderer;

    Shader m_shader;

    Texture m_texture1;
    Texture m_texture2;

    Camera m_camera;
    const float m_sensitivity;
    bool m_firstMouse;
    float m_lastX;
    float m_lastY;

    void load_vertex_data( const std::string &filePath );
    void setup_buffer( const std::string &dataPath );
    void load_texture( const std::string &filePath, Texture &texture );

    void mouse_callback( GLFWwindow *window, double xPos, double yPos );
    void scroll_callback( GLFWwindow *window, double xOffset, double yOffset );

    static void mouse_callback_wrapper( GLFWwindow* window, double xPos, double yPos )
    {
        // This static method needs to somehow know which instance to use
        Application* app = static_cast<Application*>( glfwGetWindowUserPointer( window ) );
        app->mouse_callback( window, xPos, yPos );
    }

    static void scroll_callback_wrapper( GLFWwindow *window, double xOffset, double yOffset )
    {
        Application* app = static_cast<Application*>( glfwGetWindowUserPointer( window ) );
        app->scroll_callback( window, xOffset, yOffset );
    }

    ImGuiIO& setup_imGui();

public:
    Application( GLFWwindow *window );

    ~Application();

    void run();
};