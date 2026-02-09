#include <glad/gl.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

namespace Renderer 
{
    // Axes shader sources
    const char* axesVertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;

        out vec3 vColor;

        uniform mat4 u_Model;
        uniform mat4 u_View;
        uniform mat4 u_Projection;

        void main()
        {
            vColor = aColor;
            gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);
        }
    )";

    const char* axesFragmentSource = R"(
        #version 330 core
        in vec3 vColor;
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(vColor,1.0);
        }
    )";

    Renderer::Renderer(GLFWwindow* window) : m_window(window)
    {
        if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
            throw std::runtime_error("Failed to initialize GLAD");

        // Setup basic transformations matrices
        m_model = glm::mat4(1.0f);

        InitAxesShaders();
        InitAxes();
        m_grid = std::make_unique<Grid>(10, 1.0f);
    }

    Renderer::~Renderer() 
    {
        glDeleteVertexArrays(1, &m_axesVAO);
        glDeleteBuffers(1, &m_axesVBO);
        glDeleteProgram(m_axesShaderProgram);

        glDeleteVertexArrays(1, &m_triangleVAO);
        glDeleteBuffers(1, &m_triangleVBO);
        glDeleteProgram(m_triangleShaderProgram);
    }

    void Renderer::InitAxesShaders()
    {
        m_axesShader = std::make_unique<Shader>(
        axesVertexShaderSource,
        axesFragmentSource
        );
        m_axesShaderProgram = m_axesShader->GetID();
    }

    void Renderer::InitAxes() 
    {
        float axesVertices[] = {
            // X axis (red)
            0,0,0, 1,0,0,
            1,0,0, 1,0,0,
            // Y axis (green)
            0,0,0, 0,1,0,
            0,1,0, 0,1,0,
            // Z axis (blue)
            0,0,0, 0,0,1,
            0,0,1, 0,0,1
        };

        glGenVertexArrays(1, &m_axesVAO);
        glGenBuffers(1, &m_axesVBO);

        glBindVertexArray(m_axesVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_axesVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(axesVertices), axesVertices, GL_STATIC_DRAW);

        //position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void Renderer::Clear(float r, float g, float b, float a) 
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::DrawAxes(const EditorCamera& camera)
    {
        glDisable(GL_DEPTH_TEST);
        glUseProgram(m_axesShaderProgram);

        glUniformMatrix4fv(glGetUniformLocation(m_axesShaderProgram, "u_Model"), 1, GL_FALSE, glm::value_ptr(m_model));
        glUniformMatrix4fv(glGetUniformLocation(m_axesShaderProgram, "u_View"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(m_axesShaderProgram, "u_Projection"), 1, GL_FALSE, glm::value_ptr(camera.GetProjectionMatrix()));

        glBindVertexArray(m_axesVAO);
        glDrawArrays(GL_LINES, 0, 6);
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::Render(const EditorCamera& camera)
    {
        m_grid->Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());
        DrawAxes(camera);
    }

    void Renderer::SwapBuffers() { glfwSwapBuffers(m_window); }
}
