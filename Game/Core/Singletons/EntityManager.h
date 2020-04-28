#pragma once

#include <Core/Utility/Noncopyable.h>
#include <Core/Utility/Nonmoveable.h>
#include <Core/CoreDefs.h>
#include <map>
#include <memory>

class Entity;

class EntityManager : public Noncopyable, public Nonmoveable
{
public:
	CORE_API static EntityManager Instance;
	CORE_API Entity* CreateEntity();
	CORE_API Entity* GetEntityByUID(const size_t uid);
private:
	EntityManager() = default;
	~EntityManager() = default;
	std::map<size_t, std::unique_ptr<Entity>> entities;
};