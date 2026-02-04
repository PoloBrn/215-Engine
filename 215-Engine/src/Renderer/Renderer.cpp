#include <glad/gl.h>
#include <iostream>
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

namespace Renderer 
{
    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        void main()
        {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(1.0, 0.5, 0.2, 1.0);
        }
    )";


    Renderer::Renderer(GLFWwindow* window) : m_window(window), m_VAO(0), m_VBO(0), m_shaderProgram(0)
    {
        if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
        {
            throw std::runtime_error("Failed to initialize GLAD");
        }
        
        InitShaders();
        InitTriangle();
    }

    Renderer::~Renderer() 
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
    }

    void Renderer::InitShaders() 
    {
        Shader shader(vertexShaderSource, fragmentShaderSource);
        m_shaderProgram = shader.GetID();
    }

    void Renderer::InitTriangle() 
    {
        float vertices[] = {
             0.0f,  0.5f, 0.0f, // top
            -0.5f, -0.5f, 0.0f, // bottom left
             0.5f, -0.5f, 0.0f  // bottom right
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 
    }

    void Renderer::Clear(float r, float g, float b, float a) 
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::DrawTriangle() 
    {
        glUseProgram(m_shaderProgram);
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void Renderer::SwapBuffers() 
    {
        glfwSwapBuffers(m_window);
    }
}
