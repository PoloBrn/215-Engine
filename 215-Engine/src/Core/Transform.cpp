#include "Core/Transform.h"

namespace Core
{
    Transform::Transform(): m_position(0.0f), m_rotation(glm::identity<glm::quat>()), m_scale(1.0f) {}

    const glm::vec3& Transform::GetPosition() const { return m_position; }

    const glm::quat& Transform::GetRotation() const { return m_rotation; }

    const glm::vec3& Transform::GetScale() const { return m_scale; }

    void Transform::SetPosition(const glm::vec3& position) { m_position = position; }

    void Transform::SetRotation(const glm::quat& rotation) { m_rotation = rotation; }

    void Transform::SetScale(const glm::vec3& scale) { m_scale = scale; }

    glm::mat4 Transform::GetWorldMatrix() const
    {
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_position);
        glm::mat4 rotation = glm::mat4_cast(m_rotation);
        glm::mat4 scale = glm::translate(glm::mat4(1.0f), m_scale);
        return translation * rotation * scale;
    }
}