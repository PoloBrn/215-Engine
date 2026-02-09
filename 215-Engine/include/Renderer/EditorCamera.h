#pragma once
#include <glm/glm.hpp>

namespace Renderer
{
    class EditorCamera
    {
        public:
            EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

            void Update();

            const glm::mat4& GetViewMatrix() const;
            const glm::mat4& GetProjectionMatrix() const;

        private:
            void RecalculateView();
            void RecalculateProjection();

            float m_fov;
            float m_aspectRatio;
            float m_nearClip;
            float m_farClip;

            float m_yaw;
            float m_pitch;
            float m_distance;

            glm::vec3 m_target;
            glm::vec3 m_position;

            glm::mat4 m_view;
            glm::mat4 m_projection;
    };
}