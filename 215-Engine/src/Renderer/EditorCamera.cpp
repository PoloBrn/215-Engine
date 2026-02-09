#include "Renderer/EditorCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

namespace Renderer
{
    EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip) :
    m_fov(fov), m_aspectRatio(aspectRatio), m_nearClip(nearClip), m_farClip(farClip),
    m_yaw(-90.0f), m_pitch(-30.0f), m_distance(5.0f), m_target(0.0f, 0.0f, 0.0f)
    {
        RecalculateProjection();
        RecalculateView();
    }

    void EditorCamera::Update()
    {
        // --- Input handling for orbit / pan / zoom ---

        // Orbit (Alt + Left Mouse Button)
        if (Core::Input::GetMouseButton(GLFW_MOUSE_BUTTON_LEFT))
        {
            float dx = Core::Input::GetAxisMouseX();
            float dy = Core::Input::GetAxisMouseY();

            m_yaw   += dx * 0.1f;   // Sensitivity factor
            m_pitch += dy * 0.1f;

            // Clamp pitch to avoid flipping
            if (m_pitch > 89.0f) m_pitch = 89.0f;
            if (m_pitch < -89.0f) m_pitch = -89.0f;
        }

        // Pan (Alt + Middle Mouse Button)
        if (Core::Input::GetMouseButton(GLFW_MOUSE_BUTTON_MIDDLE))
        {
            float dx = Core::Input::GetAxisMouseX() * 0.01f * m_distance;
            float dy = Core::Input::GetAxisMouseY() * 0.01f * m_distance;

            // Move the target in camera space
            glm::vec3 right = glm::normalize(glm::cross(GetForwardDirection(), glm::vec3(0,1,0)));
            glm::vec3 up    = glm::vec3(0,1,0);

            m_target -= right * dx;
            m_target += up * dy;
        }

        // Zoom (Alt + Right Mouse Button or scroll)
        if (Core::Input::GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT))
        {
            float dy = Core::Input::GetAxisMouseY();
            m_distance -= dy * 0.05f;
        }

        // Scroll zoom
        float scroll = Core::Input::GetAxisScroll();
        if (scroll != 0.0f)
            m_distance -= scroll * 0.2f;

        // Recalculate view after input
        RecalculateView();
    }

    void EditorCamera::RecalculateProjection()
    {
        m_projection = glm::perspective(
            glm::radians(m_fov),
            m_aspectRatio,
            m_nearClip,
            m_farClip
        );
    }

    void EditorCamera::RecalculateView()
    {
        float yawRad = glm::radians(m_yaw);
        float pitchRad = glm::radians(m_pitch);

        glm::vec3 direction;
        direction.x = cos(pitchRad) * cos(yawRad);
        direction.y = sin(pitchRad);
        direction.z = cos(pitchRad) * sin(yawRad);

        m_position = m_target - glm::normalize(direction) * m_distance;
        m_view = glm::lookAt(m_position, m_target, glm::vec3(0, 1, 0));
    }

    glm::vec3 EditorCamera::GetForwardDirection() const
    {
        float yawRad = glm::radians(m_yaw);
        float pitchRad = glm::radians(m_pitch);

        glm::vec3 forward;
        forward.x = cos(pitchRad) * cos(yawRad);
        forward.y = sin(pitchRad);
        forward.z = cos(pitchRad) * sin(yawRad);
        return glm::normalize(forward);
    }

    const glm::mat4& EditorCamera::GetViewMatrix() const { return m_view; }

    const glm::mat4& EditorCamera::GetProjectionMatrix() const { return m_projection; }
}