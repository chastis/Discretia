#include <Core/Components/AttachComponent.h>
#include <Core/Components/CollisionComponent.h>
#include <Core/Entity.h>
#include <Core/Consts/Consts.h>
#include <cmath>

AttachComponent* Attacheable::GetAttachOwner() const
{
    return attachedOwner;
}

bool AttachComponent::IsAttached()
{
    if (attached)
    {
        const auto attachComp =  attached->GetComponent<Attacheable>();
        const auto myCollision = owner->GetComponent<CollisionComponent>();
        const auto attachedCollision = attached->GetComponent<CollisionComponent>();
        if (myCollision && attachedCollision && attachComp)
        {
            if (myCollision->CheckCollision(attachedCollision))
            {
                attachComp->attachedOwner = this;
                return true;
            }
        }
    }
    attached = nullptr;
    return false;
}

bool AttachComponent::TryAttach(Entity* entity)
{
    if (!IsAttached() || entity->GetUID() == attached->GetUID())
    {
        if (!entity) return false;
        const auto attachComp =  entity->GetComponent<Attacheable>();
        if (!attachComp) return false;
        attachComp->attachedOwner = this;
        attached = entity;
        return true;
    }
    return false;
}

Entity* AttachComponent::GetAttached()
{
    IsAttached();
    return attached;
}
