#include <Core/Singletons/EntityManager.h>
#include <Core/Entity.h>

void EntityManager::Init()
{
    entities.clear();
}

const std::map<size_t, std::unique_ptr<Entity>>& EntityManager::GetEntities() const
{
    return entities;
}

Entity* EntityManager::CreateEntity()
{
    std::unique_ptr<Entity> newEntity = std::make_unique<Entity>();
    newEntity->Init();
    Entity* newEntityPtr = newEntity.get();
    entities[newEntity->GetUID()] = std::move(newEntity);
    return newEntityPtr;
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

