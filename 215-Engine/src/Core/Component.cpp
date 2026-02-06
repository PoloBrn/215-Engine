#include "Core/Component.h"
#include "Core/Entity.h"

namespace Core
{
    Entity* Component::GetEntity() const { return m_entity; }

    void Component::SetEntity(Entity* entity) { m_entity = entity; }
}