#pragma once

#include <Core/Prototypes/SpritePrototype.h>
#include <Core/Components/BaseComponent.h>
#include <Core/Interfaces/PrototypeableInterface.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>

class CORE_API DrawableComponent : public BaseComponent, public sf::Sprite, public PrototypeableInterface<SpritePrototype>
{
public:
    void InitFromPrototype() override;
    void Update(float deltaTime) override;
    size_t zIndex = 0;

    static size_t GetNewMaxIndexZ();
protected:
    static size_t maxIndexZ;
};