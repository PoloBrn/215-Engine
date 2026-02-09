#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Renderer/Shader.h"

namespace Renderer
{
    class Grid
    {
        public:
            Grid(int size = 10, float step = 1.0f);
            ~Grid();

            void Draw(const glm::mat4& view, const glm::mat4& projection);

        private:
            unsigned int m_VAO, m_VBO;
            int m_lines;
            std::unique_ptr<Shader> m_shader;
    };
}