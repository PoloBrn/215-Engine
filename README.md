# 215-Engine
Project to create my own 3D engine to improve and understand how a 3D engine works.

# Preambles
- CMake 3.16 or higher
- A C++17 compatible compiler
- GLFW

# Directory Structure
- `215-Engine/`: The core engine source code and headers.
- `215-Engine-Sandbox/`: A sandbox application to test and demonstrate engine features.

# Building the Project
## Clone GLFW
```
mkdir external
cd external
git clone https://github.com/glfw/glfw.git
set VCPKG_ROOT=
```

## Build CMake
```
rmdir /s /q build
mkdir build
cd build
cmake .. -A x64
cmake --build .
```

# Running the Sandbox
After building, navigate to the `215-Engine-Sandbox/build/` directory and run the `215-Engine-Sandbox.exe` executable to see the engine in action.