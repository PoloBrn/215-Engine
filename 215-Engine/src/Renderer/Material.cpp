#include <glad/gl.h>
#include "Renderer/Material.h"

namespace Renderer
{
    Material::Material()
    {
        m_shader = std::make_shared<Shader>(
            R"(#version 330 core
               layout(location = 0) in vec3 aPos;
               uniform mat4 u_Model;
               uniform mat4 u_View;
               uniform mat4 u_Projection;
               void main() { gl_Position = u_Projection * u_View * u_Model * vec4(aPos,1.0); })",
            R"(#version 330 core
               out vec4 FragColor;
               void main() { FragColor = vec4(1.0,0.8,0.2,1.0); })"
        );
    }

    Material::Material(std::shared_ptr<Shader> shader): m_shader(shader) { }

    void Material::Bind() const { if(m_shader) m_shader->Use(); }

    void Material::SetMat4(const std::string& name, const glm::mat4& value)
    {
        if (m_shader) glUniformMatrix4fv(glGetUniformLocation(m_shader->GetID(), name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
}