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
    if (auto attachedShared = attached.lock())
    {
        const auto attachComp =  attachedShared->GetComponent<Attacheable>();
        const auto myCollision = owner->GetComponent<CollisionComponent>();
        const auto attachedCollision = attachedShared->GetComponent<CollisionComponent>();
        if (myCollision && attachedCollision && attachComp)
        {
            if (myCollision->CheckCollision(attachedCollision))
            {
                attachComp->attachedOwner = this;
                return true;
            }
        }
    }
    attached.reset();
    return false;
}

bool AttachComponent::TryAttach(Entity* entity)
{
    if (!IsAttached() || entity->GetUID() == attached.lock()->GetUID())
    {
        if (!entity) return false;
        const auto attachComp =  entity->GetComponent<Attacheable>();
        if (!attachComp) return false;
        attachComp->attachedOwner = this;
        attached = entity->weak_from_this();
        return true;
    }
    return false;
}

Entity* AttachComponent::GetAttached()
{
    IsAttached();
    return attached.lock().get();
}
