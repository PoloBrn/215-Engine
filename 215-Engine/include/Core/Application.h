#pragma once
#include "Platform/Window.h"
#include "Renderer/Renderer.h"
#include <memory>

namespace Core 
{
    class Application
    {
        public:
            Application(std::unique_ptr<Platform::Window> window);
            ~Application();

            // Starts the main application loop
            void Run();

        private:
            bool m_running; // Indicates if the application is running
            std::unique_ptr<Platform::Window> m_window; // The application window
            std::unique_ptr<Renderer::Renderer> m_renderer; // The renderer
    };
}
