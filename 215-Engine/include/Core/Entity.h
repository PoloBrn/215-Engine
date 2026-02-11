#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
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
            template<typename T> bool HasComponent() const;

            void Start();
            void Update();

            void SetParent(Entity* parent);
            Entity* GetParent() const;
            void AddChild(std::unique_ptr<Entity> child);
            const std::vector<std::unique_ptr<Entity>>& GetChildren() const;

            Entity* FindChildByName(const std::string& name);
            void ListChildren(int indent = 0) const;

            void SetName(const std::string& name) { m_name = name; }
            const std::string& GetName() { return m_name; }

        private:
            std::string m_name;
            Transform m_transform;
            std::vector<std::unique_ptr<Component>> m_components;
            bool m_started = false;

            Entity* m_parent = nullptr;
            std::vector<std::unique_ptr<Entity>> m_children;
    };
    
    template<typename T> bool Entity::HasComponent() const
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for (const auto& component : m_components)
        {
            if (dynamic_cast<T*>(component.get()))
                return true;
        }
        return false;
    }

    template<typename T, typename... Args> T* Entity::AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->SetEntity(this);

        T* rawPtr = component.get();
        m_components.emplace_back(std::move(component));

        if (m_started)
            rawPtr->OnStart();

        std::cout << "ADDING COMPONENT" << std::endl;
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