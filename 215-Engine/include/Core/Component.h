#pragma once

namespace Core
{
    class Entity;

    class Component
    {
        public:
            virtual ~Component() = default;

            virtual void OnStart() {}
            virtual void OnUpdate() {}
            virtual void OnDestroy() {}

            Entity* GetEntity() const;

        private:
            Entity* m_entity = nullptr;
            friend class Entity;
            void SetEntity(Entity* entity);
    };
}