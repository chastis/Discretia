#include <Core/Singletons/EntityManager.h>
#include <Core/Entity.h>
#include <Core/Components/DrawableComponent.h>
#include <Core/Components/CollisionComponent.h>
#include <Core/Singletons/GameManager.h>

void EntityManager::Init()
{
    entities.clear();
    sortedEntities.clear();
}

const std::map<size_t, std::shared_ptr<Entity>>& EntityManager::GetEntities() const
{
    return entities;
}

const std::vector<Entity*>& EntityManager::GetSortedEntities(bool resort)
{
    if (resort)
    {
        SortEntities();
    }
    return sortedEntities;
}

void EntityManager::ActivateEntity(bool resort)
{
    if (resort)
    {
        SortEntities();
    }
    bool flag = true;
    for (auto entity = sortedEntities.rbegin(); entity != sortedEntities.rend(); ++entity)
    {
        (*entity)->bActive = false;
        if (flag)
        {
            const auto collisionComponent = (*entity)->GetComponent<CollisionComponent>();
            if (collisionComponent)
            {
                const auto mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(GameManager::GetInstance().GetWindow()));
                if (collisionComponent->CheckCollision(mousePos.x, mousePos.y))
                {
                    (*entity)->bActive = true;
                    activeEntity = (*entity);
                    flag = false;
                }
            }
        }
    }
    if (flag)
    {
        activeEntity = nullptr;
    }
}

Entity* EntityManager::GetActiveEntity(bool resort)
{
    if (resort)
    {
        ActivateEntity(resort);
    }
    return activeEntity;
}

Entity* EntityManager::CreateEntity()
{
    std::shared_ptr<Entity> newEntity = std::make_shared<Entity>();/*std::make_unique<Entity>();*/
    newEntity->Init();
    Entity* newEntityPtr = newEntity.get();
    sortedEntities.push_back(newEntityPtr);
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

std::vector<Entity*> EntityManager::GetEntitiesBtySID(const std::string& sid) const
{
    std::vector<Entity*> entities;
    for (const auto& ent : sortedEntities)
    {
        if (ent && ent->GetPrototype().GetSID() == sid)
        {
            entities.push_back(ent);
        }
    }
    return entities;
}

void EntityManager::RemoveEntityByUID(const size_t uid)
{
    for (auto it = sortedEntities.begin(); it != sortedEntities.end(); ++it)
    {
        if (*it && (*it)->GetUID() == uid)
        {
            sortedEntities.erase(it);
            break;
        }
    }
    entities.erase(uid);
}

void EntityManager::UpdateEntities(float deltaTime)
{
    for (auto entity : sortedEntities)
    {
        entity->Update(deltaTime);
    }
}

void EntityManager::SortEntities()
{
    std::sort(sortedEntities.begin(), sortedEntities.end(), [](Entity* a, Entity* b)
        {
            if (a && b)
            {
                const auto aDraw = a->GetComponent<DrawableComponent>();
                const auto bDraw = b->GetComponent<DrawableComponent>();
                if (aDraw && bDraw)
                {
                    return aDraw->zIndex < bDraw->zIndex;
                }
            }
            return false;
        });
}

