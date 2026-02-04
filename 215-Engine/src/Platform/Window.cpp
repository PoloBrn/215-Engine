#include "Platform/Window.h"
#include <stdexcept>

namespace Platform 
{
    Window::Window(int width, int height, const std::string& title) 
    {
        // Initialize GLFW if it hasn't been initialized yet
        if (!glfwInit()) 
        {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        // Create a GLFW window
        GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) 
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        m_windowHandle = static_cast<void*>(window);
    }

    Window::~Window() 
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(m_windowHandle);
        if (window) 
        {
            glfwDestroyWindow(window);
        }
        glfwTerminate();
    }

    void Window::pollEvents() 
    {
        glfwPollEvents();
    }

    bool Window::shouldClose() const 
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(m_windowHandle);
        return glfwWindowShouldClose(window);
    }
}