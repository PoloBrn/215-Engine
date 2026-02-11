#pragma once
#include "Platform/Window.h"
#include "Renderer/Renderer.h"
#include "Core/Input.h"
#include "Core/Scene.h"
#include "Core/Time.h"
#include "Core/RenderSystem.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <queue>
#include <mutex>
#include <thread>
#include <string>

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
            void TerminalThread();
            void ProcessCommands();

            bool m_running; // Indicates if the application is running
            std::unique_ptr<Platform::Window> m_window; // The application window
            std::unique_ptr<Renderer::Renderer> m_renderer; // The renderer
            Scene m_scene;
            Renderer::EditorCamera m_editorCamera;

            //Terminal Inputs
            std::thread m_terminalThread;
            std::queue<std::string> m_commandQueue;
            std::mutex m_queueMutex;
    };
}
