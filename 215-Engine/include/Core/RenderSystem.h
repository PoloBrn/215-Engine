#pragma once
#include "Core/Scene.h"
#include "Renderer/EditorCamera.h"
#include "Core/MeshRenderer.h"

namespace Core
{
    class RenderSystem
    {
        public:
            void Render(Scene& scene, Renderer::EditorCamera& camera);
    };
}