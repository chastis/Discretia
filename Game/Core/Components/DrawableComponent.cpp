#include <Core/Components/DrawableComponent.h>

void DrawableComponent::SetSprite(const sf::Texture& texture, const size_t newZIndex)
{
	sprite.setTexture(texture);
	zIndex = newZIndex;
}

void DrawableComponent::SetSpriteFrame(const sf::IntRect& rect)
{
	sprite.setTextureRect(rect);
}

const sf::Sprite& DrawableComponent::GetSprite() const
{
	return sprite;
}

size_t DrawableComponent::GetZIndex() const
{
	return zIndex;
}
