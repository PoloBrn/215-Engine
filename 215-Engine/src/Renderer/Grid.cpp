#include <glad/gl.h>
#include "Renderer/Grid.h"
#include "Renderer/Shader.h"
#include <glm/gtc/type_ptr.hpp>

namespace Renderer
{
    Grid::Grid(int size, float step)
        : m_lines(size * 2 + 1)// centre + lines oneach side
    {
        std::vector<float> vertices;

        // Generate lines
        for (int i = -size; i <= size; ++i)
        {
            float linePos = i * step;
            
            vertices.push_back(-size * step); vertices.push_back(0.0f); vertices.push_back(linePos);
            vertices.push_back( size * step); vertices.push_back(0.0f); vertices.push_back(linePos);
            
            vertices.push_back(linePos); vertices.push_back(0.0f); vertices.push_back(-size * step);
            vertices.push_back(linePos); vertices.push_back(0.0f); vertices.push_back( size * step);
        }

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        m_shader = std::make_unique<Shader>(
            R"(
            #version 330 core
            layout(location=0) in vec3 aPos;
            uniform mat4 u_View;
            uniform mat4 u_Projection;
            void main() { gl_Position = u_Projection * u_View * vec4(aPos, 1.0); }
            )",
            R"(
            #version 330 core
            out vec4 FragColor;
            uniform vec3 u_Color;
            void main() { FragColor = vec4(0.5, 0.5, 0.5, 1.0); }
            )"
        );
    }

    Grid::~Grid()
    {
        glDeleteBuffers(1, &m_VBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void Grid::Draw(const glm::mat4& view, const glm::mat4& projection)
    {
        m_shader->Use();
        unsigned int shaderID = m_shader->GetID();
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_View"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderID, "u_Projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_LINES, 0, m_lines * 4); // each line = 2 points, 2 directions
        glBindVertexArray(0);
    }
}