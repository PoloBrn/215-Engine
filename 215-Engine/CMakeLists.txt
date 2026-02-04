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
    src/Platform/Window.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/Shader.cpp
)

# include for headers
target_include_directories(Engine PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/glfw/include
)

# link GLFW (assumed installed via package manager)
find_package(OpenGL REQUIRED)
target_link_libraries(Engine PRIVATE glfw glad OpenGL::GL)