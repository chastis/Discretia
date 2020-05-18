#pragma once

#include <Core/Prototypes/SpritePrototype.h>
#include <Core/Components/BaseComponent.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>

class CORE_API DrawableComponent : public BaseComponent, public sf::Sprite
{
public:
    void IniFromPrototype(const SpritePrototype& spritePrototype);
    //void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    size_t zIndex = 0;
};