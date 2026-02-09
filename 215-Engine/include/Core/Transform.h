#pragma once
#include "Core/Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Core 
{
    class Transform : Component
    {
        public:
            Transform();

            const glm::vec3& GetPosition() const;
            const glm::quat& GetRotation() const;
            const glm::vec3& GetScale() const;

            void SetPosition(const glm::vec3& position);
            void SetRotation(const glm::quat& rotation);
            void SetScale(const glm::vec3& scale);

            glm::mat4 GetWorldMatrix() const;

        private:
            glm::vec3 m_position;
            glm::quat m_rotation;
            glm::vec3 m_scale;
    };
}