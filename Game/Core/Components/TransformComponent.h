#pragma once

#include <Core/Components/BaseComponent.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics/Transformable.hpp>

class CORE_API TransformComponent : public BaseComponent, public sf::Transformable
{
public:
    void Update(float deltaTime) override;
    void MoveTo(sf::Vector2f location);
    bool moving = false;
protected:
    float speed = 42.f;
    sf::Vector2f desiredLocation;
    
};