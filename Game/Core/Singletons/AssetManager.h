#pragma once

#include <Core/Singletons/BaseSingleton.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

class CORE_API AssetManager : public BaseSingleton<AssetManager>
{
public:
    void Init() override;
    [[nodiscard]] sf::Texture* GetTexture(const std::string& sid) const;
    [[nodiscard]] const sf::Font* GetFont() const;
private:
    std::map<std::string, std::unique_ptr<sf::Texture>> textures;
    sf::Font font; 
};