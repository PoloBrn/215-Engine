#pragma once
#include <glfw/glfw3.h>
#include <unordered_map>

namespace Core
{
    class Input
    {
        public:
            static void Initialize(GLFWwindow* window);
            static void Update();

            // Keyboard
            static bool GetKey(int key);
            static bool GetKeyDown(int key);
            static bool GetKeyUp(int key);

            // Mouse buttons
            static bool GetMouseButton(int button);
            static bool GetMouseButtonDown(int button);
            static bool GetMouseButtonUp(int button);

            // Axes
            static float GetAxisMouseX();
            static float GetAxisMouseY();
            static float GetAxisScroll();

        private:
            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void MouseCallback(GLFWwindow* window, int button, int action, int mods);
            static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
            static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

            static std::unordered_map<int, bool> s_keys;
            static std::unordered_map<int, bool> s_keysDown;
            static std::unordered_map<int, bool> s_keysUp;

            static std::unordered_map<int, bool> s_mouseButtons;
            static std::unordered_map<int, bool> s_mouseButtonsDown;
            static std::unordered_map<int, bool> s_mouseButtonsUp;

            static float s_mouseX;
            static float s_mouseY;
            static float s_lastMouseX;
            static float s_lastMouseY;

            static float s_mouseDeltaX;
            static float s_mouseDeltaY;
            static float s_scrollDelta;
    };
}