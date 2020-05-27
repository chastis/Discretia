#pragma once

#include <Core/CoreDefs.h>

class Entity;

class CORE_API BaseComponent
{
public:
    virtual void Init(Entity* inOwner);
    virtual void Update(float deltaTime);
    virtual  ~BaseComponent() = default;
protected:
    Entity* owner = nullptr;
};
