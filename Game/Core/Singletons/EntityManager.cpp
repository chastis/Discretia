#include <Core/Singletons/EntityManager.h>
#include <Core/Entity.h>

EntityManager EntityManager::Instance;

Entity* EntityManager::CreateEntity()
{
	std::unique_ptr<Entity> newEntity = std::make_unique<Entity>();
	newEntity->Init();
	entities[newEntity->GetUID()] = std::move(newEntity);
	return newEntity.get();
}

Entity* EntityManager::GetEntityByUID(const size_t uid)
{
	const auto it = entities.find(uid);
	if (it != entities.end())
	{
		return it->second.get();
	}
	return nullptr;
}

