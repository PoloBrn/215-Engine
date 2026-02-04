# 215-Engine
Project to create my own 3D engine to improve and understand how a 3D engine works.

# Preambles
- CMake 3.16 or higher
- A C++17 compatible compiler
- GLFW
- GLAD (OpenGL loader)
- GLM (OpenGL Mathematics)

# Directory Structure
- `215-Engine/`: The core engine source code and headers.
- `215-Engine-Sandbox/`: A sandbox application to test and demonstrate engine features.
- `external/`: Third-party libraries and dependencies.

# Building the Project
## 1. Clone GLFW
```
mkdir external
cd external
git clone https://github.com/glfw/glfw.git
set VCPKG_ROOT=
```

## 2. Add GLAD
Download GLAD from https://gen.glad.sh/ with the following settings:
- Language: C/C++
- Specification: OpenGL
- Profile: Core
- API: gl version 4.6
- Generate a loader: Yes

## 3. Clone GLM
```
cd external
git clone https://github.com/g-truc/glm/tree/master
set VCPKG_ROOT=
```

Click generate and download the .zip file. Extract the contents and place the `include` and `src` folders inside `external/glad/`.

## Build CMake
```
rmdir /s /q build
mkdir build
cd build
cmake .. -A x64
cmake --build .
```

# Running the Sandbox
After building, navigate to the `MyEngine_215\build\215-Engine-Sandbox\Debug` directory and run the `Sandbox.exe` executable to see the engine in action.