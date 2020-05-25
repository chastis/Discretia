#include <Core/Components/CollisionComponent.h>
#include <Core/Entity.h>
#include <Core/Components/TransformComponent.h>
#include <Core/Components/DrawableComponent.h>

void CollisionComponent::Init(Entity* inOwner)
{
    owner = inOwner;
    if (owner)
    {
        ownerTransform = owner->GetComponent<TransformComponent>();
        if (!ownerTransform)
        {
            __debugbreak();
        }

    }
}

void CollisionComponent::InitFromPrototype()
{
    if (!prototype)
    {
        prototype = &CollisionPrototypes::GetDefault();
    }
    if (prototype->UseDrawable())
    {
        InitFromDrawable();
    }
}

void CollisionComponent::InitFromDrawable()
{
    if (owner)
    {
        const auto ownerDrawable = owner->GetComponent<DrawableComponent>();
        if (ownerDrawable)
        {
            setScale(ownerDrawable->getScale());
            setOrigin(ownerDrawable->getOrigin());
            setPosition(ownerDrawable->getPosition());
            setRotation(ownerDrawable->getRotation());
        }
        else
        {
            __debugbreak();
        }
    }
}

bool CollisionComponent::CheckCollision(const sf::Vector2f& point) const
{
    return CheckCollision(point.x, point.y);
}

bool CollisionComponent::CheckCollision(const CollisionComponent* firstCollision, const CollisionComponent* secondCollision)
{
    if (firstCollision && secondCollision)
    {
        switch (firstCollision->collisionType)
        {
        case CollisionTypes::Box:
            switch (secondCollision->collisionType)
            {
            case CollisionTypes::Box:
                return CheckBoxCollisions(firstCollision, secondCollision);
            case CollisionTypes::None:
            default:
                __debugbreak();
            }
        case CollisionTypes::None:
        default:
            __debugbreak();
        }
    }
    return false;
}

bool CollisionComponent::CheckCollision(const CollisionComponent* collisionComponent) const
{
    return CheckCollision(this, collisionComponent);
}

CollisionTypes CollisionComponent::GetCollisionType() const
{
    return collisionType;
}

bool CollisionComponent::CheckBoxCollisions(const CollisionComponent* firstCollision, const CollisionComponent* secondCollision)
{
    const auto firstBox = dynamic_cast<const BoxCollisionComponent*>(firstCollision);
    const auto secondBox = dynamic_cast<const BoxCollisionComponent*>(secondCollision);
    if (firstBox && secondBox && firstBox->ownerTransform && secondBox->ownerTransform)
    {
        const sf::FloatRect firstBoxWorldSpace = (firstBox->ownerTransform->getTransform() * firstBox->getTransform()).transformRect(firstBox->GetCollisionBox());
        const sf::FloatRect secondBoxWorldSpace = (secondBox->ownerTransform->getTransform() * firstBox->getTransform()).transformRect(secondBox->GetCollisionBox());
        return firstBoxWorldSpace.intersects(secondBoxWorldSpace) || secondBoxWorldSpace.intersects(firstBoxWorldSpace);
    }
    return false;
}

void BoxCollisionComponent::InitFromDrawable()
{
    CollisionComponent::InitFromDrawable();
    if (owner)
    {
        const auto ownerDrawable = owner->GetComponent<DrawableComponent>();
        if (ownerDrawable)
        {
            collisionBox = ownerDrawable->getLocalBounds();
        }
    }
}

bool BoxCollisionComponent::CheckCollision(float x, float y) const
{
    if (ownerTransform)
    {
        const auto BoxWorldSpace = (ownerTransform->getTransform() * getTransform()).transformRect(collisionBox);
        return BoxWorldSpace.contains(x, y);
    }
    return false;
}

const sf::FloatRect& BoxCollisionComponent::GetCollisionBox() const
{
    return collisionBox;
}


BoxCollisionComponent::BoxCollisionComponent()
{
    collisionType = CollisionTypes::Box;
}
