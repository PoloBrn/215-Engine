#include <glad/gl.h>
#include "Renderer/Gizmo.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

namespace Renderer
{
    Gizmo::Gizmo()
        : m_target(nullptr), m_mode(Translate)
    {
        // Create VAO/VBO once
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        m_shader = std::make_unique<Shader>(
            R"(
                #version 330 core
                layout(location = 0) in vec3 aPos;
                uniform mat4 u_View;
                uniform mat4 u_Projection;
                void main() { gl_Position = u_Projection * u_View * vec4(aPos, 1.0); }
            )",
            R"(
                #version 330 core
                out vec4 FragColor;
                void main() { FragColor = vec4(1,1,1,1); }
            )"
        );
    }

    Gizmo::~Gizmo()
    {
        glDeleteBuffers(1, &m_VBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void Gizmo::Draw(const glm::mat4& view, const glm::mat4& projection, Core::Entity* selected)
    {
        m_target = selected;
        if (!m_target) return;

        glm::vec3 pos = m_target->GetTransform().GetPosition();
        float axisLength = 1.0f;

        float vertices[] = {
            // X axis (red)
            pos.x, pos.y, pos.z, pos.x + axisLength, pos.y, pos.z,
            // Y axis (green)
            pos.x, pos.y, pos.z, pos.x, pos.y + axisLength, pos.z,
            // Z axis (blue)
            pos.x, pos.y, pos.z, pos.x, pos.y, pos.z + axisLength
        };

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        m_shader->Use();
        glUniformMatrix4fv(glGetUniformLocation(m_shader->GetID(), "u_View"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(m_shader->GetID(), "u_Projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glDrawArrays(GL_LINES, 0, 6);
        glBindVertexArray(0);
    }

    void Gizmo::OnMouseDrag(const glm::vec2& mouseDelta, EditorCamera& camera)
    {
        if (!m_target) return;

        // TODO: add translate/rotate/scale of m_mode
    }
}