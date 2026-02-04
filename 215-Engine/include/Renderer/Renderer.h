#pragma once
#include "Renderer/Shader.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Renderer 
{
    class Renderer
    {
        public:
            Renderer(GLFWwindow* window);
            ~Renderer();

            void Clear(float r, float g, float b, float a);
            void DrawTriangle();
            void SwapBuffers();

        private:
            GLFWwindow* m_window;

            unsigned int m_VAO;
            unsigned int m_VBO;
            unsigned int m_shaderProgram;

            glm::mat4 m_Model;
            glm::mat4 m_View;
            glm::mat4 m_Projection;

            void InitTriangle();
            void InitShaders();
    };
}