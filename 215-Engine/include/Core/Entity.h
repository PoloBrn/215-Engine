#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include "Core/Transform.h"
#include "Core/Component.h"

namespace Core
{
    class Entity
    {
        public:
            Entity();
            ~Entity() = default;

            Transform& GetTransform();
            const Transform& GetTransform() const;

            template<typename T, typename... Args> T* AddComponent(Args&&... args);
            template<typename T> T* GetComponent() const;

            void Start();
            void Update(float deltaTime);

        private:
            Transform m_transform;
            std::vector<std::unique_ptr<Component>> m_components;
            bool m_started = false;
    };

    template<typename T, typename... Args> T* Entity::AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->SetEntity(this);

        T* rawPtr = component.get();
        m_components.emplace_back(std::move(component));

        if (m_started)
            rawPtr->OnStart();

        return rawPtr;
    };

    template<typename T> T* Entity::GetComponent() const
    {
        for (const auto& component : m_components)
        {
            if (auto casted = dynamic_cast<T*>(component.get()))
                return casted;
        }
        return nullptr;
    };
}