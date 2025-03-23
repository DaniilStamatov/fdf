#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define YAW -90.0f
#define PITCH 0.0f
#define SPEED 2.5f
#define SENSITIVITY 0.01f
#define ZOOM 45.0f

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
   public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH)
        : m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
          m_movementSpeed(SPEED),
          m_mouseSensitivity(SENSITIVITY),
          m_zoom(ZOOM) {
        m_position = position;
        m_worldUp = up;
        m_yaw = yaw;
        m_pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() { return glm::lookAt(m_position, m_position + m_front, m_up); }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        float velocity = m_movementSpeed * deltaTime;
        if (direction == FORWARD) m_position = m_position + (m_front * velocity);
        if (direction == BACKWARD) m_position = m_position - (m_front * velocity);
        if (direction == LEFT) m_position = m_position - (m_right * velocity);
        if (direction == RIGHT) m_position = m_position + (m_right * velocity);
    }

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true) {
        xoffset *= m_mouseSensitivity;
        yoffset *= m_mouseSensitivity;

        m_yaw += xoffset;
        m_pitch += yoffset;

        if (constrainPitch) {
            if (m_pitch > 89.0f) m_pitch = 89.0f;
            if (m_pitch < -89.0f) m_pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void updateCameraVectors() {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch) );
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);

        // also re-calculate the Right and Up vector
        m_right = glm::normalize(glm::cross(m_front, m_worldUp));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }

    void ProcessMouseScroll(float yoffset) {
        m_zoom -= (float)yoffset;
        if (m_zoom < 1.0f) m_zoom = 1.0f;
        if (m_zoom > 45.0f) m_zoom = 45.0f;
    }

    float GetZoom() const { return m_zoom; }
    glm::vec3 GetPosition() const {return m_position;}
   private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    // euler Angles
    float m_yaw;
    float m_pitch;
    // camera options
    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;
};