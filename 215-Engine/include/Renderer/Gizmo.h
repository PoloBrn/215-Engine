#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Entity.h"
#include "Renderer/EditorCamera.h"
#include "Renderer/Shader.h"
#include <memory>

namespace Renderer
{
    enum GizmoMode { Translate, Rotate, Scale };
    
    class Gizmo
    {
        public:
            Gizmo();
            ~Gizmo();

            void Draw(const glm::mat4& view, const glm::mat4& projection, Core::Entity* selected);
            void OnMouseDrag(const glm::vec2& mouseDelta, EditorCamera& camera);

        private:
            GizmoMode m_mode;
            Core::Entity* m_target;

            unsigned int m_VAO, m_VBO;
            std::unique_ptr<Shader> m_shader;
    };
}
