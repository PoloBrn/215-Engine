#pragma once
#include "Renderer/Shader.h"
#include <GLFW/glfw3.h>

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

            void InitTriangle();
            void InitShaders();
    };
}