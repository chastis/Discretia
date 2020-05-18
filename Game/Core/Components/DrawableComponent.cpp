#include <Core/Components/DrawableComponent.h>
#include <Core/Singletons/AssetManager.h>

void DrawableComponent::IniFromPrototype(const SpritePrototype& spritePrototype)
{
    sf::Texture* newTexture = AssetManager::GetInstance().GetTexture(spritePrototype.getTextureSID());
    if (newTexture)
    {
        setTexture(*newTexture);
    }
    setTextureRect(spritePrototype.getRect());
}
