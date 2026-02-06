#include "Core/Input.h"
#include <iostream>
#include <algorithm>

namespace Core
{
    bool Input::s_firstMouse = true;
    float Input::s_lastX = 400.0f;
    float Input::s_lastY = 300.0f;

    void Input::Initialize(GLFWwindow* window)
    {
        
    }

    void Input::Update(GLFWwindow* window, float deltaTime)
    {

    }

    void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        // Add later shortcuts
    }

    void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos)
    {
        
    }

    void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        
    }
}