#include "Core/Entity.h"

namespace Core
{
    Entity::Entity(): m_started(false) {}

    Transform& Entity::GetTransform() { return m_transform; }

    const Transform& Entity::GetTransform() const { return m_transform; }

    void Entity::Start()
    {
        if (m_started) return;

        for (auto& component : m_components) component->OnStart();

        m_started = true;
    }

    void Entity::Update(float deltaTime)
    {
        if (!m_started) Start();

        for (auto& component : m_components) component->OnUpdate(deltaTime);
    }
}