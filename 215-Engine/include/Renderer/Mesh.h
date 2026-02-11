#pragma once
#include <vector>

namespace Renderer
{
    class Mesh
    {
    public:
        Mesh();
        Mesh(const std::vector<float>& vertices);
        ~Mesh();

        void Bind() const;
        void Draw() const;

    private:
        unsigned int m_VAO;
        unsigned int m_VBO;
        unsigned int m_vertexCount;
    };
}