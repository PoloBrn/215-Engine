#include "Core/RenderSystem.h"

namespace Core
{
    void RenderSystem::Render(Scene& scene, Renderer::EditorCamera& camera)
    {
        for (auto& entity : scene.GetRootEntities())
        {
            if (!entity->HasComponent<MeshRenderer>()) continue;

            auto mr = entity->GetComponent<MeshRenderer>();
            auto mesh = mr->GetMesh();
            auto material = mr->GetMaterial();
            if (!mesh || !material) continue;

            material->Bind();
            material->SetMat4("u_Model", entity->GetTransform().GetWorldMatrix());
            material->SetMat4("u_View", camera.GetViewMatrix());
            material->SetMat4("u_Projection", camera.GetProjectionMatrix());
            mesh->Bind();
            mesh->Draw();
        }
    }
}