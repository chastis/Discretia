#include <Core/Components/DrawableComponent.h>
#include <Core/Singletons/AssetManager.h>

void DrawableComponent::InitFromPrototype()
{
    if (prototype)
    {
        sf::Texture* newTexture = AssetManager::GetInstance().GetTexture(prototype->getTextureSID());
        if (newTexture)
        {
            setTexture(*newTexture);
        }
        setTextureRect(prototype->getRect());
        setScale(prototype->getScale());
    }
    else
    {
        __debugbreak();
    }
}
