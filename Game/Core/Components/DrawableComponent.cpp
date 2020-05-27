#include <Core/Components/DrawableComponent.h>
#include <Core/Singletons/AssetManager.h>
#include <cstdint>
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
    if (interpSpeed != 0.f)
    {
        if (getColor() == desiredColor)
        {
            desiredColor = sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255 );
        }
        auto interp = [this](auto current, auto desired, float deltaTime)
        {
            if (std::abs(current)+deltaTime*interpSpeed > std::abs(desired))
            {
                current = desired;
            }
            else
            {
                current += static_cast<decltype(current)>(desired*deltaTime * (desired-current)/std::abs(desired-current));
            }
            return current;
        };

        const sf::Color currentColor = getColor();

        const sf::Color newColor = sf::Color(interp(currentColor.r, desiredColor.r, deltaTime), 
            interp(currentColor.g, desiredColor.g, deltaTime), 
            interp(currentColor.b, desiredColor.b, deltaTime));
        setColor(newColor);

    }
}

void DrawableComponent::ChangeInterpRandomColor(float interp)
{
    interpSpeed = interp;
}

size_t DrawableComponent::GetNewMaxIndexZ()
{
    return maxIndexZ++;
}
