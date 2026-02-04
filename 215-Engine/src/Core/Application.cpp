#include "Core/Application.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace Core 
{
    Application::Application(std::unique_ptr<Platform::Window> window) : m_window(std::move(window)), m_running(false)
    {
        if (!m_window) throw std::invalid_argument("Window pointer is null");
        
        m_renderer = std::make_unique<Renderer::Renderer>(m_window->getGLFWwindow());        
    }

    Application::~Application() 
    {
        // Destructor implementation
    }

    void Application::Run() 
    {
        m_running = true;
        std::cout << "Application started." << std::endl;

        // Main application loop
        while (m_running && !m_window->shouldClose()) 
        {
            m_window->pollEvents();

            m_renderer->Clear(0.1f, 0.1f, 0.1f, 1.0f);
            m_renderer->DrawTriangle();
            m_renderer->SwapBuffers();
        }

        std::cout << "Application stopped." << std::endl;
    }
}
