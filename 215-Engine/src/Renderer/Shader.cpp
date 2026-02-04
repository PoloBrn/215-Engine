#include <glad/gl.h>
#include "Renderer/Shader.h"
#include <iostream>

namespace Renderer 
{
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentSrc) 
    {
        // For simplicity, we assume the shader sources are provided as strings.
        unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexPath);
        unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShader);
        glAttachShader(m_ID, fragmentShader);
        glLinkProgram(m_ID);

        // Check for linking errors
        int success;
        char infoLog[512];
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success) 
        {
            glGetProgramInfoLog(m_ID, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader() 
    {
        glDeleteProgram(m_ID);
    }

    void Shader::Use() const 
    {
        glUseProgram(m_ID);
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source) 
    {
        unsigned int shader = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        // Check for compilation errors
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) 
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        return shader;
    }
}