#include <Core/Components/DrawableComponent.h>
#include <Core/Singletons/AssetManager.h>

size_t DrawableComponent::maxIndexZ = 2;

void DrawableComponent::InitFromPrototype()
{
    if (prototype)
    {
        sf::Texture* newTexture = AssetManager::GetInstance().GetTexture(prototype->getTextureSID());
        if (newTexture)
        {
            setTexture(*newTexture);
        }
        if (prototype->getRect().has_value())
        {
            setTextureRect(prototype->getRect().value());
        }
        else
        {
            setTextureRect({0, 0, static_cast<int>(newTexture->getSize().x), static_cast<int>(newTexture->getSize().y)});
        }
        if (prototype->UseScaleTo())
        {
            setScale(prototype->getScale().x / getTextureRect().width, prototype->getScale().y / getTextureRect().height);
        }
        else
        {
            setScale(prototype->getScale());
        }
        zIndex = prototype->GetZIndex();
    }
    else
    {
        __debugbreak();
    }
}

void DrawableComponent::Update(float deltaTime)
{
}

size_t DrawableComponent::GetNewMaxIndexZ()
{
    return maxIndexZ++;
}
