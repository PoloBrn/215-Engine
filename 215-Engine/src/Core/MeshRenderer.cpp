#include "Core/MeshRenderer.h"
#include <glm/gtc/type_ptr.hpp>

namespace Core
{
    MeshRenderer::MeshRenderer()
    {
        m_mesh = std::make_shared<Renderer::Mesh>();
        m_material = std::make_shared<Renderer::Material>();
    }

    MeshRenderer::MeshRenderer(std::shared_ptr<Renderer::Mesh> mesh, std::shared_ptr<Renderer::Material> material):
    m_mesh(mesh), m_material(material) { }
}