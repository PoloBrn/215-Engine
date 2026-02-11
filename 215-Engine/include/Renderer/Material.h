#pragma once
#include "Renderer/Shader.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Renderer
{
    class Material
    {
    public:
        Material();
        Material(std::shared_ptr<Shader> shader);

        void Bind() const;
        void SetMat4(const std::string& name, const glm::mat4& value);

    private:
        std::shared_ptr<Shader> m_shader;
    };
}