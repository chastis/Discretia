#pragma once

#include <Core/Components/BaseComponent.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>

class CORE_API DrawableComponent : public BaseComponent
{
public:
	void SetSprite(const sf::Texture& texture, const size_t newZIndex = 0);
	void SetSpriteFrame(const sf::IntRect& rect);
	const sf::Sprite& GetSprite() const;
	size_t GetZIndex() const;
private:
	sf::Sprite sprite;
	size_t zIndex = 0;
};