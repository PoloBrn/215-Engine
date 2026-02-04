#pragma once
#include <string>

namespace Renderer 
{
    class Shader
    {
        public:
            Shader(const std::string& vertexPath, const std::string& fragmentSrc);
            ~Shader();

            void Use() const;
            unsigned int GetID() const { return m_ID; }

        private:
            unsigned int m_ID; // OpenGL shader program ID

            unsigned int CompileShader(unsigned int type, const std::string& source);
    };
}