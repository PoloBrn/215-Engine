#pragma once
#include <vector>
#include <memory>
#include "Core/Entity.h"
#include "Renderer/EditorCamera.h"

namespace Core
{
    class Scene
    {
        public:
            Entity& CreateEntity(const std::string& name);
            Entity* Pick(const glm::vec2& mousePos, const Renderer::EditorCamera& camera, const glm::ivec2& viewportSize);
            void Update();

            const std::vector<std::unique_ptr<Entity>>& GetRootEntities() const { return m_entities; }
            void ListHierarchy() const;

        private:
            std::vector<std::unique_ptr<Entity>> m_entities;
    };
}