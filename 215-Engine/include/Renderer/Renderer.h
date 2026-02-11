#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "Renderer/Shader.h"
#include "Renderer/EditorCamera.h"
#include "Renderer/Grid.h"

namespace Renderer 
{
    class Renderer
    {
        public:
            Renderer(GLFWwindow* window);
            ~Renderer();

            void Clear(float r, float g, float b, float a);
            void Render(const EditorCamera& camera);
            void SwapBuffers();

        private:
            GLFWwindow* m_window;
            std::unique_ptr<Grid> m_grid;

            // axes
            unsigned int m_axesVAO, m_axesVBO;
            unsigned int m_axesShaderProgram;

            // triangle
            unsigned int m_triangleVAO, m_triangleVBO;
            unsigned int m_triangleShaderProgram;

            glm::mat4 m_model;
            
            std::unique_ptr<Shader> m_axesShader;

            void InitAxes();
            void InitAxesShaders();
            void DrawAxes(const EditorCamera& camera);
    };
}