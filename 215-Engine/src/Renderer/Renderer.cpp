#include <glad/gl.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

namespace Renderer 
{
    const char* vertexShaderSource = R"(
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
            throw std::runtime_error("Failed to initialize GLAD");
        
        InitShaders();
        InitTriangle();

        // Setup basic transformations
        m_Model = glm::mat4(1.0f);
        m_View = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m_Projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
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
            -0.5f, -0.5f, 0.5f, // left, front
             0.5f, 0.5f, 0.0f  // right, front
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

        unsigned int modelLoc = glGetUniformLocation(m_shaderProgram, "u_Model");
        unsigned int viewLoc = glGetUniformLocation(m_shaderProgram, "u_View");
        unsigned int projLoc = glGetUniformLocation(m_shaderProgram, "u_Projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_Model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_View));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_Projection));

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void Renderer::SwapBuffers() 
    {
        glfwSwapBuffers(m_window);
    }
}
