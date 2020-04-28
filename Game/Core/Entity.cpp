#include <Core/Entity.h>
#include <Core/Singletons/UIDManager.h>

void Entity::Init()
{
	UID = UIDManager::Instance.Register();
}

