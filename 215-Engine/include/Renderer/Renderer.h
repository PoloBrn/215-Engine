#pragma once
#include "Renderer/Shader.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

namespace Renderer 
{
    class Renderer
    {
        public:
            Renderer(GLFWwindow* window);
            ~Renderer();

            void Clear(float r, float g, float b, float a);
            void Render();
            void SwapBuffers();

        private:
            GLFWwindow* m_window;

            // axes
            unsigned int m_axesVAO, m_axesVBO;
            unsigned int m_axesShaderProgram;

            // triangle
            unsigned int m_triangleVAO, m_triangleVBO;
            unsigned int m_triangleShaderProgram;

            glm::mat4 m_model;
            glm::mat4 m_view;
            glm::mat4 m_projection;
            
            std::unique_ptr<Shader> m_axesShader;
            std::unique_ptr<Shader> m_triangleShader;

            void InitMatrices();

            void InitAxes();
            void InitAxesShaders();
            void DrawAxes();

            void InitTriangle();
            void InitTriangleShaders();
            void DrawTriangle();
    };
}