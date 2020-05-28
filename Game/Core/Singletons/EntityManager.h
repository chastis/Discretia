#pragma once

#include <Core/Singletons/BaseSingleton.h>
#include <Core/CoreDefs.h>
#include <map>
#include <memory>
#include <vector>
#include <string>

class Entity;

class CORE_API EntityManager : public BaseSingleton<EntityManager>
{
public:
    void Init() override;
    [[nodiscard]] const std::map<size_t, std::shared_ptr<Entity>>& GetEntities() const;
    [[nodiscard]] const std::vector<Entity*>& GetSortedEntities(bool resort = true);
    void ActivateEntity(bool resort = true);
    Entity* GetActiveEntity(bool resort = true);
    Entity* CreateEntity();
    Entity* GetEntityByUID(const size_t uid);
    [[nodiscard]] std::vector<Entity*> GetEntitiesBtySID(const std::string& sid) const;
    void RemoveEntityByUID(const size_t uid);
    void UpdateEntities(float deltaTime);
private:
    void SortEntities();

    std::map<size_t, std::shared_ptr<Entity>> entities;
    std::vector<Entity*> sortedEntities;
    Entity* activeEntity = nullptr;
};