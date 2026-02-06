#include "Core/Application.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace Core 
{
    Application::Application(std::unique_ptr<Platform::Window> window) : m_window(std::move(window)), m_running(false)
    {
        if (!m_window) throw std::invalid_argument("Window pointer is null");
        GLFWwindow* glfwWindow = m_window->getGLFWwindow();
        glfwFocusWindow(glfwWindow);
        glfwMakeContextCurrent(glfwWindow);
        m_renderer = std::make_unique<Renderer::Renderer>(m_window->getGLFWwindow());
        glEnable(GL_DEPTH_TEST);
        Core::Input::Initialize(m_window->getGLFWwindow());   
    }

    Application::~Application() 
    {
        // Destructor implementation
    }

    void Application::Run() 
    {
        m_running = true;
        std::cout << "Application started." << std::endl;
        float lastFrame = 0.0f;

        // Main application loop
        while (m_running && !m_window->shouldClose()) 
        {
            float currentFrame = static_cast<float>(glfwGetTime());
            float deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            m_window->pollEvents();

            m_renderer->Clear(0.1f, 0.1f, 0.1f, 1.0f);
            m_renderer->Render();
            m_renderer->SwapBuffers();
            Core::Input::Update(m_window->getGLFWwindow(), deltaTime);
        }

        std::cout << "Application stopped." << std::endl;
    }
}
