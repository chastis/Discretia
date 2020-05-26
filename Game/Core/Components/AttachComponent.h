#pragma once

#include <Core/Components/BaseComponent.h>
#include <Core/CoreDefs.h>

class Entity;

class CORE_API Attacheable : public BaseComponent
{
    friend class AttachComponent;
public:
    [[nodiscard]] AttachComponent* GetAttachOwner() const;
protected:
    AttachComponent* attachedOwner = nullptr;
};

class CORE_API AttachComponent : public BaseComponent
{
public:
    bool IsAttached();
    bool TryAttach(Entity* entity);
    Entity* GetAttached();
protected:
   Entity* attached = nullptr;
    
};