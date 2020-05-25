#pragma once

#include <Core/Interfaces/PrototypeableInterface.h>
#include <Core/Prototypes/CollisionPrototype.h>
#include <Core/Components/BaseComponent.h>
#include <Core/Consts/Enums.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>

class TransformComponent;

class CORE_API CollisionComponent : public BaseComponent, public sf::Transformable, public PrototypeableInterface<CollisionPrototype>
{
public:

    virtual ~CollisionComponent() = default;
    void Init(Entity* inOwner) override;
     void InitFromPrototype() override;

    bool CheckCollision(const sf::Vector2f& point) const;
    virtual bool CheckCollision(float x, float y) const = 0;
    static bool CheckCollision(const CollisionComponent* firstCollision, const CollisionComponent* secondCollision);
    bool CheckCollision(const CollisionComponent* collisionComponent) const;

    [[nodiscard]] CollisionTypes GetCollisionType() const;
protected:
    CollisionTypes collisionType = CollisionTypes::None;
    TransformComponent* ownerTransform = nullptr;

    virtual void InitFromDrawable();
    static bool CheckBoxCollisions(const CollisionComponent* firstCollision, const CollisionComponent* secondCollision);
};

class CORE_API BoxCollisionComponent : public CollisionComponent
{
public:

    bool CheckCollision(float x, float y) const override;
    [[nodiscard]] const sf::FloatRect& GetCollisionBox() const;
    BoxCollisionComponent();
protected:
    sf::FloatRect collisionBox;

    void InitFromDrawable() override;
};

