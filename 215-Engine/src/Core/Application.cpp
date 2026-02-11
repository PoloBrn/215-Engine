#include "Core/Application.h"

namespace Core
{
    Application::Application(std::unique_ptr<Platform::Window> window) : 
    m_window(std::move(window)), m_running(false), m_editorCamera(45.0f, 800.0f / 600.0f, 0.1f, 100.0f)
    {
        if (!m_window) throw std::invalid_argument("Window pointer is null");
        GLFWwindow* glfwWindow = m_window->getGLFWwindow();
        glfwFocusWindow(glfwWindow);
        glfwMakeContextCurrent(glfwWindow);
        std::cout << "Window and glad initialized successfully." << std::endl;
        m_renderer = std::make_unique<Renderer::Renderer>(m_window->getGLFWwindow());
        glEnable(GL_DEPTH_TEST);
        Core::Input::Initialize(m_window->getGLFWwindow());   
    }

    Application::~Application()
    {
        m_running = false;
        if (m_terminalThread.joinable()) m_terminalThread.join();
    }

    void Application::TerminalThread()
    {
        while (m_running)
        {
            std::string cmd;
            if (!std::getline(std::cin, cmd))
                break; // std::cin closed or error

            if (!cmd.empty())
            {
                std::lock_guard<std::mutex> lock(m_queueMutex);
                m_commandQueue.push(cmd);
            }
        }
    }

    void Application::ProcessCommands()
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        while (!m_commandQueue.empty())
        {
            std::string cmd = m_commandQueue.front();
            m_commandQueue.pop();

            if (cmd == "add tri")
            {
                Entity& tri = m_scene.CreateEntity("Triangle2D");
                tri.GetTransform().SetPosition({0.0f, 0.0f, 0.0f});
                tri.AddComponent<MeshRenderer>();
                std::cout << "Entity created: " << tri.GetName() << " GUID: " << tri.GetGUID() << std::endl;
            }
            else if (cmd.find("delete ") == 0)
            {
                std::string guid = cmd.substr(7);
                if (m_scene.RemoveEntityByGUID(guid)) std::cout << "Entity with GUID " << guid << " removed.\n";
                else std::cout << "No Entity with GUID " << guid << " found.\n";
            }
            else if (cmd == "list")
            {
                std::cout << "Scene hierarchy:\n";
                m_scene.ListHierarchy();
            }
            else if (cmd.find("find ") == 0)
            {
                std::string guid = cmd.substr(5);
                Entity* e = m_scene.FindEntityByGUID(guid);
                if (e) std::cout << "Found entity: " << e->GetName() << "\n";
                else std::cout << "No entity with GUID " << guid << "\n";
            }
        }
    }

    void Application::Run() 
    {
        m_running = true;
        std::cout << "Application started." << std::endl;
        std::thread(&Application::TerminalThread, this).detach(); // Start terminal thread

        RenderSystem rs;
        // Main application loop
        while (m_running && !m_window->shouldClose()) 
        {
            float currentFrame = static_cast<float>(glfwGetTime());
            Core::Time::Update(currentFrame);

            m_window->pollEvents();
            
            Core::Input::Update();
            m_editorCamera.Update();

            ProcessCommands();
            m_renderer->Clear(0.1f, 0.1f, 0.1f, 1.0f);
            m_scene.Update();
            m_renderer->Render(m_editorCamera);
            rs.Render(m_scene, m_editorCamera);
            m_renderer->SwapBuffers();
        }

        m_running = false; // Stop terminal thread
        if (m_terminalThread.joinable()) m_terminalThread.join();

        std::cout << "Application stopped." << std::endl;
    }
}