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

    Entity* Scene::Pick(const glm::vec2& mousePos, const Renderer::EditorCamera& camera, const glm::ivec2& viewportSize)
    {
        float x = (2.0f * mousePos.x) / viewportSize.x - 1.0f;
        float y = 1.0f - (2.0f * mousePos.y) / viewportSize.y;
        glm::vec4 rayClip(x, y, -1.0f, 1.0f);

        glm::vec4 rayEye = glm::inverse(camera.GetProjectionMatrix()) * rayClip;
        rayEye.z = -1.0f;
        rayEye.w = 0.0f;

        glm::vec3 rayWorld = glm::normalize(glm::vec3(glm::inverse(camera.GetViewMatrix()) * rayEye));
        glm::vec3 origin = camera.GetPosition();

        // Intersection AABB
        Entity* picked = nullptr;
        float minDist = FLT_MAX;

        for (auto& e : m_entities)
        {
            glm::vec3 pos = e->GetTransform().GetPosition();
            glm::vec3 minB = pos - glm::vec3(0.5f);
            glm::vec3 maxB = pos + glm::vec3(0.5f);

            float tMin = 0.0f, tMax = 1000.0f;
            for (int i = 0; i < 3; ++i)
            {
                if (fabs(rayWorld[i]) < 1e-6) continue;
                float t1 = (minB[i] - origin[i]) / rayWorld[i];
                float t2 = (maxB[i] - origin[i]) / rayWorld[i];
                if (t1 > t2) std::swap(t1, t2);
                tMin = t1 > tMin ? t1 : tMin;
                tMax = t2 < tMax ? t2 : tMax;
                if (tMin > tMax) break;
            }

            if (tMin < tMax && tMin < minDist)
            {
                minDist = tMin;
                picked = e.get();
            }
        }

        return picked;
    }
}