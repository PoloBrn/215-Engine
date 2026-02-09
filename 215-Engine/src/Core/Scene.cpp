#include "Core/Scene.h"

namespace Core
{
    Entity& Scene::CreateEntity()
    {
        auto entity = std::make_unique<Entity>();
        Entity& ref = *entity;
        m_entities.emplace_back(std::move(entity));
        return ref;
    }

    void Scene::Update()
    {
        for (auto& entity : m_entities) entity->Update();
    }
}