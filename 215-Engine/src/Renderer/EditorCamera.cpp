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

    const glm::mat4& EditorCamera::GetViewMatrix() const { return m_view; }

    const glm::mat4& EditorCamera::GetProjectionMatrix() const { return m_projection; }
}