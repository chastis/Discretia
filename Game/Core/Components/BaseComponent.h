#pragma once

#include <Core/CoreDefs.h>

class Entity;

class CORE_API BaseComponent
{
public:
    virtual void Init(Entity* inOwner);
    virtual  ~BaseComponent() = default;

protected:
    Entity* owner = nullptr;
};
