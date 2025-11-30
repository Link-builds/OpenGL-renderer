#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
    glm::vec3 m_CameraPos;
    glm::vec3 m_CameraFront;
    glm::vec3 m_CameraUp;
    glm::mat4 m_LookAt;

    float m_Pitch;
    float m_Yaw;
    float m_Zoom;
    float m_Fov;

public:
    // Camera() {};
    Camera( const glm::vec3 &pos, const glm::vec3 &front, const glm::vec3 &up );

    ~Camera() {};

    void camera_keyborad_input( GLFWwindow *window, float cameraSpeed );
    glm::mat4 get_lookAt() const;
    float get_fov() const;
    void update_direction();

    void set_position( const glm::vec3 &pos, const glm::vec3 &front, const glm::vec3 &up );

    friend void mouse_callback( GLFWwindow *window, double xPos, double yPos );
    friend void scroll_callback( GLFWwindow *window, double xOffset, double yOffset );
    friend class Application;
};