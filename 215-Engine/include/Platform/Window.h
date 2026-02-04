#pragma once
#include <GLFW/glfw3.h>
#include <string>

namespace Platform 
{
    class Window
    {
        public:
            Window(int width, int height, const std::string& title);
            ~Window();

            // Polls for window events
            void pollEvents();

            // Checks if the window should close
            bool shouldClose() const;

            GLFWwindow* getGLFWwindow() const { return static_cast<GLFWwindow*>(m_windowHandle); };

        private:
            void* m_windowHandle; // Opaque handle to the window
    };
}
