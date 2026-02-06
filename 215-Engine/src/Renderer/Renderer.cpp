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

    // Triangle shader source
    const char* triangleVertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;

        uniform mat4 u_Model;
        uniform mat4 u_View;
        uniform mat4 u_Projection;

        void main()
        {
            gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);
        }
    )";

    const char* triangleFragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(1.0, 0.5, 0.2, 1.0);
        }
    )";

    Renderer::Renderer(GLFWwindow* window) : m_window(window)
    {
        if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
            throw std::runtime_error("Failed to initialize GLAD");

        // Setup basic transformations matrices
        m_model = glm::mat4(1.0f);
        m_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m_projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        InitMatrices();
        InitAxesShaders();
        InitAxes();
        InitTriangleShaders();
        InitTriangle();
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

    void Renderer::InitMatrices()
    {
        m_model = glm::mat4(1.0f);
        m_view = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        m_projection = glm::perspective(
            glm::radians(45.0f),
            800.0f / 600.0f,
            0.1f,
            100.0f
        );
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

    void Renderer::InitTriangleShaders()
    {
        m_triangleShader = std::make_unique<Shader>(
        triangleVertexShaderSource,
        triangleFragmentShaderSource
        );
        m_triangleShaderProgram = m_triangleShader->GetID();
    }

    void Renderer::InitTriangle() 
    {
        float vertices[] = {
            0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
        };
        
        glGenVertexArrays(1, &m_triangleVAO);
        glGenBuffers(1, &m_triangleVBO);

        glBindVertexArray(m_triangleVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    void Renderer::Clear(float r, float g, float b, float a) 
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::DrawAxes()
    {
        glUseProgram(m_axesShaderProgram);

        glUniformMatrix4fv(glGetUniformLocation(m_axesShaderProgram, "u_Model"), 1, GL_FALSE, glm::value_ptr(m_model));
        glUniformMatrix4fv(glGetUniformLocation(m_axesShaderProgram, "u_View"), 1, GL_FALSE, glm::value_ptr(m_view));
        glUniformMatrix4fv(glGetUniformLocation(m_axesShaderProgram, "u_Projection"), 1, GL_FALSE, glm::value_ptr(m_projection));

        glBindVertexArray(m_axesVAO);
        glDrawArrays(GL_LINES, 0, 6);
    }

    void Renderer::DrawTriangle() 
    {
        glUseProgram(m_triangleShaderProgram);

        glUniformMatrix4fv(glGetUniformLocation(m_triangleShaderProgram, "u_Model"), 1, GL_FALSE, glm::value_ptr(m_model));
        glUniformMatrix4fv(glGetUniformLocation(m_triangleShaderProgram, "u_View"), 1, GL_FALSE, glm::value_ptr(m_view));
        glUniformMatrix4fv(glGetUniformLocation(m_triangleShaderProgram, "u_Projection"), 1, GL_FALSE, glm::value_ptr(m_projection));

        glBindVertexArray(m_triangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void Renderer::Render()
    {
        glUseProgram(m_axesShaderProgram);
        DrawAxes();

        // glUseProgram(m_triangleShaderProgram);
        // DrawTriangle();
    }

    void Renderer::SwapBuffers() 
    {
        glfwSwapBuffers(m_window);
    }
}
