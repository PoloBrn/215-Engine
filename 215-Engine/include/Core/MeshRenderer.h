#pragma once
#include "Core/Component.h"
#include "Core/Entity.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"
#include "Renderer/EditorCamera.h"
#include <memory>

namespace Core
{
    class MeshRenderer : public Component
    {
    public:
        MeshRenderer();
        MeshRenderer(
            std::shared_ptr<Renderer::Mesh> mesh,
            std::shared_ptr<Renderer::Material> material
        );

        std::shared_ptr<Renderer::Mesh> GetMesh() const { return m_mesh; }
        std::shared_ptr<Renderer::Material> GetMaterial() const { return m_material; }

    private:
        std::shared_ptr<Renderer::Mesh> m_mesh;
        std::shared_ptr<Renderer::Material> m_material;
    };
}