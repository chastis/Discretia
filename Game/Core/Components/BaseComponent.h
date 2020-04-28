#pragma once

#include <Core/CoreDefs.h>

class Entity;

class CORE_API BaseComponent
{
public:
	void Init(Entity* inOwner);

private:
	Entity* owner = nullptr;
};
