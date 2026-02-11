#include "Core/Entity.h"
#include <iostream>

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

    void Entity::Update()
    {
        if (!m_started) Start();

        for (auto& component : m_components) component->OnUpdate();
    }

    void Entity::SetParent(Entity* parent) { m_parent = parent; }

    Entity* Entity::GetParent() const { return m_parent; }

    void Entity::AddChild(std::unique_ptr<Entity> child)
    {
        child->SetParent(this);
        m_children.push_back(std::move(child));
    }

    const std::vector<std::unique_ptr<Entity>>& Entity::GetChildren() const { return m_children; }

    Entity* Entity::FindChildByName(const std::string& name)
    {
        for (auto& c : m_children)
        {
            if (c->GetName() == name) return c.get();
            Entity* found = c->FindChildByName(name);
            if (found) return found;
        }
        return nullptr;
    }

    void Entity::ListChildren(int indent) const
    {
        for (auto& c : m_children)
        {
            std::cout << std::string(indent, ' ') << "- " << c->GetName() << "\n";
            c->ListChildren(indent + 2);
        }
    }
}