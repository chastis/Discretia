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
