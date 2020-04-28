#pragma once

#include <Core/CoreDefs.h>

class Entity;

class CORE_DLL BaseComponent
{
public:
	void Init(Entity* InOwner);

private:
	Entity* Owner = nullptr;
};