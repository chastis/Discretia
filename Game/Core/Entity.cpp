#include <Core/Entity.h>
#include <Core/Singletons/UIDManager.h>

void Entity::Init()
{
    uid = UIDManager::GetInstance().Register();
}

size_t Entity::GetUID() const
{
    return uid;
}

