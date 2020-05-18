#pragma once

#include <Core/Singletons/BaseSingleton.h>
#include <Core/CoreDefs.h>
#include <map>
#include <memory>

class Entity;

class CORE_API EntityManager : public BaseSingleton<EntityManager>
{
public:
    void Init() override;
    const std::map<size_t, std::unique_ptr<Entity>>& GetEntities() const;
    Entity* CreateEntity();
    Entity* GetEntityByUID(const size_t uid);
private:
    std::map<size_t, std::unique_ptr<Entity>> entities;
};