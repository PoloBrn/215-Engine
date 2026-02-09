#include "Core/Input.h"

namespace Core
{
    std::unordered_map<int, bool> Input::s_keys;
    std::unordered_map<int, bool> Input::s_keysDown;
    std::unordered_map<int, bool> Input::s_keysUp;

    std::unordered_map<int, bool> Input::s_mouseButtons;
    std::unordered_map<int, bool> Input::s_mouseButtonsDown;
    std::unordered_map<int, bool> Input::s_mouseButtonsUp;

    float Input::s_mouseX = 0.0f;
    float Input::s_mouseY = 0.0f;
    float Input::s_lastMouseX = 0.0f;
    float Input::s_lastMouseY = 0.0f;
    float Input::s_mouseDeltaX = 0.0f;
    float Input::s_mouseDeltaY = 0.0f;
    float Input::s_scrollDelta = 0.0f;

    void Input::Initialize(GLFWwindow* window)
    {
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetMouseButtonCallback(window, MouseCallback);
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetScrollCallback(window, ScrollCallback);
    }

    void Input::Update()
    {
        s_keysDown.clear();
        s_keysUp.clear();
        s_mouseButtonsDown.clear();
        s_mouseButtonsUp.clear();

        s_mouseDeltaX = s_mouseX - s_lastMouseX;
        s_mouseDeltaY = s_lastMouseY - s_mouseY;

        s_lastMouseX = s_mouseX;
        s_lastMouseY = s_mouseY;

        s_scrollDelta = 0.0f;
    }

    bool Input::GetKey(int key) { return s_keys[key]; }
    bool Input::GetKeyDown(int key) { return s_keysDown[key]; }
    bool Input::GetKeyUp(int key) { return s_keysUp[key]; }

    bool Input::GetMouseButton(int button) { return s_mouseButtons[button]; }
    bool Input::GetMouseButtonDown(int button) { return s_mouseButtonsDown[button]; }
    bool Input::GetMouseButtonUp(int button) { return s_mouseButtonsUp[button]; }

    float Input::GetAxisMouseX() { return s_mouseDeltaX; }
    float Input::GetAxisMouseY() { return s_mouseDeltaY; }
    float Input::GetAxisScroll() { return s_scrollDelta; }

    void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            s_keys[key] = true;
            s_keysDown[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            s_keys[key] = false;
            s_keysUp[key] = true;
        }
    }

    void Input::MouseCallback(GLFWwindow* window, int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            s_mouseButtons[button] = true;
            s_mouseButtonsDown[button] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            s_mouseButtons[button] = false;
            s_mouseButtonsUp[button] = true;
        }
    }

    void Input::CursorPosCallback(GLFWwindow*, double xpos, double ypos)
    {
        s_mouseX = static_cast<float>(xpos);
        s_mouseY = static_cast<float>(ypos);
    }

    void Input::ScrollCallback(GLFWwindow*, double, double yoffset) { s_scrollDelta += static_cast<float>(yoffset); }
}