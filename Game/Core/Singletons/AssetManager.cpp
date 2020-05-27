#include <Core/Singletons/AssetManager.h>
#include <Core/Prototypes/TexturePrototype.h>

void AssetManager::Init()
{
    for (size_t i = 0; i < TexturePrototypes::Size(); ++i)
    {
        auto newTexture = std::make_unique<sf::Texture>();
        const TexturePrototype& texturePrototype = TexturePrototypes::Get(i);
        if (newTexture->loadFromFile(CoreConst::EngineContentPath + texturePrototype.getTexturePath()))
        {
            textures[texturePrototype.GetSID()] = std::move(newTexture);
        }
    }
    const auto path = CoreConst::EngineContentPath + std::string("HeyComic.ttf");
    font.loadFromFile(path);
}

sf::Texture* AssetManager::GetTexture(const std::string& sid) const
{
    const auto it = textures.find(sid);
    if (it != textures.end())
    {
        return it->second.get();
    }
    return nullptr;
}

const sf::Font* AssetManager::GetFont() const
{
    return &font;
}
