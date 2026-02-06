#pragma once

namespace Core
{
    class Entity;

    class Component
    {
        public:
            virtual ~Component() = default;

            virtual void OnStart() {}
            virtual void OnUpdate(float deltaTime) {}

            Entity* GetEntity() const;
        
        protected:
            Entity* m_entity = nullptr;

        private:
            friend class Entity;
            void SetEntity(Entity* entity);
    };
}