#include "Core/Application.h"
#include "Platform/Window.h"
#include <iostream>
#include <memory>

int main() 
{
    try
    {
        auto window = std::make_unique<Platform::Window>(800, 600, "215 Engine Sandbox");
        Core::Application app(std::move(window));
        app.Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    return 0;
}
