#include "Core/Application.h"
#include "Core/Time.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace Core 
{
    Application::Application(std::unique_ptr<Platform::Window> window) : 
    m_window(std::move(window)), m_running(false), m_editorCamera(45.0f, 800.0f / 600.0f, 0.1f, 100.0f)
    {
        if (!m_window) throw std::invalid_argument("Window pointer is null");
        GLFWwindow* glfwWindow = m_window->getGLFWwindow();
        glfwFocusWindow(glfwWindow);
        glfwMakeContextCurrent(glfwWindow);
        m_renderer = std::make_unique<Renderer::Renderer>(m_window->getGLFWwindow());
        glEnable(GL_DEPTH_TEST);
        Core::Input::Initialize(m_window->getGLFWwindow());   
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
            Core::Time::Update(currentFrame);

            m_window->pollEvents();
            
            Core::Input::Update();
            m_editorCamera.Update();

            m_scene.Update();

            m_renderer->Clear(0.1f, 0.1f, 0.1f, 1.0f);
            m_renderer->Render(m_editorCamera);
            m_renderer->SwapBuffers();
        }

        std::cout << "Application stopped." << std::endl;
    }
}
