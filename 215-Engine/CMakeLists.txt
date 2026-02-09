cmake_minimum_required(VERSION 3.16)
project(Engine)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add GLFW as an external dependency locally
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw glfw_build)

# Add GLAD
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/external/glad/src/gl.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/include)

# create library
add_library(Engine STATIC
    src/Core/Application.cpp
    src/Core/Time.cpp
    src/Core/Input.cpp
    src/Core/Scene.cpp
    src/Core/Component.cpp
    src/Core/Transform.cpp
    src/Core/Entity.cpp
    src/Platform/Window.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/Shader.cpp
    src/Renderer/EditorCamera.cpp
)

# include for headers
target_include_directories(Engine PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/glm
)

# link GLFW (assumed installed via package manager)
find_package(OpenGL REQUIRED)
target_link_libraries(Engine PRIVATE glfw glad OpenGL::GL)