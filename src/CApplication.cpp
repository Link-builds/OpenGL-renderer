#include "CApplication.h"

Application::Application( GLFWwindow *window )
    : m_window(window),
      m_VAO(new VertexArray()),
      m_sensitivity(0.1f),
      m_camera(glm::vec3( 0.0f, 0.0f, 3.0f ), glm::vec3( 0.0f, 0.0f, -1.0f ), glm::vec3( 0.0f, 1.0f, 0.0f )),
      m_shader("Shaders/shader.vert", "Shaders/shader.frag")
{
    setup_buffer( "resource/vertexData.txt" );

    m_firstMouse = true;
    m_lastX = SCR_WIDTH / 2.0f;
    m_lastY = SCR_HEIGHT / 2.0f;
}

Application::~Application()
{
    // Clear heap buffers
    delete m_VBO;
    delete m_VAO;

#if IMGUI_SET
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
#endif

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
}

void Application::load_vertex_data( const std::string &filePath )
{
    float data;
    std::ifstream input( filePath );

    if( !input )
    {
        funs::handle_err( "ERR: Failed to read file " + filePath );
    }

    while( input >> data )
    {
        m_vertices.push_back( data );
    }

    if( input.fail() && !input.eof() )
    {
        funs::handle_err( "ERR: Bad data in file " + filePath );
    }
}

void Application::setup_buffer( const std::string &dataPath )
{
    load_vertex_data( dataPath );

    m_VBO = new VertexBuffer( m_vertices.data(), m_vertices.size() * sizeof(float) );
}

void Application::load_texture( const std::string &filePath, Texture &texture )
{
    ImageLoader image( filePath );
    texture.bind();
    image.generate_texture_from_image( texture );
    texture.unbind();
}

void Application::mouse_callback( GLFWwindow *window, double xPos, double yPos )
{

#if IMGUI_SET
    ImGui_ImplGlfw_CursorPosCallback(window, xPos, yPos);

    if( glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE ) 
    {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        m_lastX = xPos;
        m_lastY = yPos;
        m_firstMouse = true;

        return ;
    }
    
#endif

    if( m_firstMouse )
    {
        m_lastX = xPos;
        m_lastY = yPos;
        m_firstMouse = false;
    }

    float xOffset = xPos - m_lastX;
    float yOffset = m_lastY - yPos;

    m_lastX = xPos;
    m_lastY = yPos;

    xOffset *= m_sensitivity;
    yOffset *= m_sensitivity;

    m_camera.m_Yaw += xOffset;
    m_camera.m_Pitch += yOffset;

    if( m_camera.m_Pitch > 89.0f )
    {
        m_camera.m_Pitch = 89.0f;
    }

    if( m_camera.m_Pitch < -89.0f )
    {
        m_camera.m_Pitch = -89.0f;
    }

    m_camera.update_direction();
}

void Application::scroll_callback( GLFWwindow *window, double xOffset, double yOffset )
{
    m_camera.m_Fov -= static_cast<float>( yOffset );

    if( m_camera.m_Fov < 1.0f )
    {
        m_camera.m_Fov = 1.0f;
    }
    
    if( m_camera.m_Fov > 45.0f )
    {
        m_camera.m_Fov = 45.0f;
    }
}

ImGuiIO& Application::setup_imGui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;           // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;            // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable docking features

    // Setup Dear ImGui style
    // ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL( m_window, true );
    ImGui_ImplOpenGL3_Init( "#version 330 core" );

    io.Fonts->AddFontDefault();

    return io;
}


void Application::run()
{
#if IMGUI_SET
    ImGuiIO& io = setup_imGui();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
#endif

    m_layout.push<float>( 3 );
    m_layout.push<float>( 2 );
    m_VAO->add_buffer( *m_VBO, m_layout );

    m_VAO->unbind();
    m_VBO->unbind();
    m_shader.unbind();

    load_texture( "resource/Textures/container.jpg", m_texture1 );
    load_texture( "resource/Textures/awesomeface.png", m_texture2 );

    m_shader.bind(); // don't forget to activate the shader before setting uniforms!  
    m_shader.setInt( "texture1", 0 );
    m_shader.setInt( "texture2", 1 );
    m_shader.setFloat( "mixRatio", 0.2f );
    m_shader.unbind();

    glm::vec3 cubePositions[] = {
        glm::vec3(  0.0f,  0.0f,  0.0f  ), 
        glm::vec3(  2.0f,  5.0f, -15.0f ), 
        glm::vec3( -1.5f, -2.2f, -2.5f  ),  
        glm::vec3( -3.8f, -2.0f, -12.3f ),  
        glm::vec3(  2.4f, -0.4f, -3.5f  ),  
        glm::vec3( -1.7f,  3.0f, -7.5f  ),  
        glm::vec3(  1.3f, -2.0f, -2.5f  ),  
        glm::vec3(  1.5f,  2.0f, -2.5f  ), 
        glm::vec3(  1.5f,  0.2f, -1.5f  ), 
        glm::vec3( -1.3f,  1.0f, -1.5f  )  
    };

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glfwSetWindowUserPointer( m_window, this );
    glfwSetCursorPosCallback( m_window, mouse_callback_wrapper);
    glfwSetScrollCallback( m_window, scroll_callback_wrapper );

    // render loop
    while( !glfwWindowShouldClose( m_window ) )
    {
        // input capture here
        float currFrame = glfwGetTime();
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;

        
        float cameraSpeed = 2.5f * deltaTime;
        bool cameraBind = true;

        funs::process_inputs( m_window );

        // TODO : FIX THIS TERRIBLENESS
        m_camera.camera_keyborad_input( m_window, cameraSpeed );

#if IMGUI_SET
        static float counter = 1.0; // Has to be static, or elseit gets reset after each loop
        static float angle = 0.0;   // and is therefore useless to implemented ImGui objects
#else
        float counter = abs( sin( glfwGetTime() ) );
        float angle = glm::degrees( static_cast<float>( glfwGetTime() ) );
#endif

#if IMGUI_SET
        // imgui prep
        if( glfwGetWindowAttrib( m_window, GLFW_ICONIFIED ) != 0)
        {
            ImGui_ImplGlfw_Sleep( 10 );
            continue;
        };

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport( 1, 0, ImGuiDockNodeFlags_PassthruCentralNode );

        // Show imGUI window
        {
            ImGui::Begin( "Settings" );

            ImGui::Text( "Change rendering options in a live environment." );

            ImGui::Text( "Rotate object" );
            ImGui::SliderFloat( "degrees", &angle, 0.0f, 180.0f );            // Edit 1 float using a slider from 0.0f to 1.0f
            
            ImGui::ColorEdit3( "Background color", (float*)&clear_color );

            if( ImGui::Button( "Scale++" ) )                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter += 0.1f;

            ImGui::SameLine();
            if ( ImGui::Button( "Reset" ) )
                counter = 1.0;

            ImGui::SameLine();
            ImGui::Text("Scale = x%.1f", counter);

            if( ImGui::Button( "Quit" ) )
                glfwSetWindowShouldClose( m_window, 1 );

            ImGui::Separator();
        
            ImVec4 green(0.043f, 0.439f, 0.125f, 1.0f);
            ImGui::PushStyleColor(ImGuiCol_Text, green);
            ImGui::Text( "Use WASD to move around, SPACE to ascend, L-SHIFT to descend" );
            ImGui::Text( "Press and hold the right mouse button to move the camera" );
            ImGui::PopStyleColor();

            ImGui::Spacing();
            ImGui::Indent( 200.0f );

            ImGui::Text( "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate );

            ImGui::End();
        };
#endif

#if IMGUI_SET
        m_renderer.set_background_color( clear_color );
#else
        m_renderer.set_background_color( 0.45f, 0.55f, 0.60f, 1.00f );
#endif

        m_renderer.clear();

        m_texture1.bind();
        m_texture2.bind( 1 );
        
        m_shader.bind();

        glm::mat4 proj;
        proj = glm::perspective( 
                                 glm::radians( m_camera.get_fov() ),
                                 static_cast<float>( SCR_WIDTH / SCR_HEIGHT ), 0.1f, 100.0f
                               );
        
        m_shader.setMat4( "view", m_camera.get_lookAt() );
        m_shader.setMat4( "proj", proj );
              
        m_VAO->bind();

        for( uint32_t i = 0; i < 10; i++ )
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4( 1.0f );
            glm::mat4 trans1 = glm::mat4( 1.0f );
            trans1 = glm::rotate( trans1, glm::radians( angle ) * glm::radians( 50.0f ), glm::vec3( 0.5f, 1.0f, 0.0f ) );
            model = glm::translate( model, cubePositions[i] );

#if IMGUI_SET
            glm::mat4 trans2 = glm::mat4( 1.0f );
            trans2 = glm::scale( trans2, glm::vec3( counter, counter, counter ) );
            model *= trans2;
#endif

            if( !( i % 2 ) )
                model *= trans1;

            m_shader.setMat4( "model", model );

            glDrawArrays( GL_TRIANGLES, 0, 36 );
        };

#if IMGUI_SET
        // Render imgui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent( m_window );
#endif

        glfwSwapBuffers( m_window );
        glfwPollEvents();
    };
}
