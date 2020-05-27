#include <Core/Components/TransformComponent.h>
#include <Core/Consts/Consts.h>
#include <cmath>
void TransformComponent::Update(float deltaTime)
{
    if (moving)
    {
        const sf::Vector2f direction = desiredLocation - getPosition();
        const float directionLength = std::hypot(direction.x, direction.y);
        if (directionLength > CoreConst::SmallValue)
        {
            const auto directionNormal = direction / directionLength;
            const auto deltaMove = direction * speed * deltaTime;
            if (std::hypot(deltaMove.x, deltaMove.y) > std::hypot(direction.x, direction.y))
            {
                setPosition(desiredLocation);
                moving = false;
            }
            else
            {
                move(deltaMove);
            }
        }
        else
        {
            moving = false;
        }
    }
}

void TransformComponent::MoveTo(sf::Vector2f location)
{
    desiredLocation = location + getOrigin();
    moving = true;
}
