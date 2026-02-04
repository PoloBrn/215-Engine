cmake_minimum_required(VERSION 3.16)
project(Sandbox)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add executable
add_executable(Sandbox src/main.cpp)

# link 215-Engine library
target_link_libraries(Sandbox PRIVATE Engine)

# include 215-Engine headers
target_include_directories(Sandbox PRIVATE ${CMAKE_SOURCE_DIR}/../215-Engine/include)