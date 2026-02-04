#include "Core/Application.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace Core 
{
    Application::Application(std::unique_ptr<Platform::Window> window) : m_window(std::move(window)), m_running(false)
    {
        if (!m_window)
        {
            throw std::invalid_argument("Window pointer is null");
        }
        
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

            // Simulate some work being done in the application
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        std::cout << "Application stopped." << std::endl;
    }
}
