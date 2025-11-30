#include "CCamera.h"


Camera::Camera( const glm::vec3 &pos, const glm::vec3 &front, const glm::vec3 &up ) : m_CameraPos(pos), m_CameraFront(front), m_CameraUp(up)
{
    m_Pitch = 0.0f;
    m_Yaw = -90.0f;
    m_Zoom = 45.0f;
    m_Fov = 45.0f;

    m_LookAt = glm::lookAt( m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp );
}

void Camera::camera_keyborad_input( GLFWwindow *window, float cameraSpeed )
{
    // m_CameraPos.y = 0.0f;

    if( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS )
        m_CameraPos += cameraSpeed * m_CameraFront;

    if( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS )
        m_CameraPos -= cameraSpeed * m_CameraFront;

    if( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS )
        m_CameraPos -= cameraSpeed * glm::normalize( glm::cross( m_CameraFront, m_CameraUp ) );

    if( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS )
        m_CameraPos += cameraSpeed * glm::normalize( glm::cross( m_CameraFront, m_CameraUp ) );

    if( glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS )
        m_CameraPos += cameraSpeed * m_CameraUp;

    if( glfwGetKey( window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS )
        m_CameraPos -= cameraSpeed * m_CameraUp;

    m_LookAt = glm::lookAt( m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp );
}

glm::mat4 Camera::get_lookAt() const
{
    return m_LookAt;
}

float Camera::get_fov() const
{
    return m_Fov;
}

void Camera::update_direction()
{
    glm::vec3 direction;

    direction.x = cos( glm::radians( m_Yaw ) ) * cos( glm::radians( m_Pitch ) );
    direction.y = sin( glm::radians( m_Pitch ) );
    direction.z = sin( glm::radians( m_Yaw ) ) * cos( glm::radians( m_Pitch ) );

    m_CameraFront = glm::normalize( direction );
    m_LookAt = glm::lookAt( m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp );
}

void Camera::set_position( const glm::vec3 &pos, const glm::vec3 &front, const glm::vec3 &up )
{
    m_CameraPos = pos;
    m_CameraFront = front;
    m_CameraUp = up;
}