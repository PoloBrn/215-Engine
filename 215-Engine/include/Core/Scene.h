#pragma once
#include <vector>
#include <memory>
#include "Core/Entity.h"

namespace Core
{
    class Scene
    {
        public:
            Entity& CreateEntity();
            void Update();

        private:
            std::vector<std::unique_ptr<Entity>> m_entities;
    };
}