#pragma once
#include <glfw/glfw3.h>

namespace Core
{
    class Input
    {
        public:
            static void Initialize(GLFWwindow* window);
            static void Update(GLFWwindow* window, float deltaTime);

        private:
            static bool s_firstMouse;
            static float s_lastX;
            static float s_lastY;

            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
            static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    };
}