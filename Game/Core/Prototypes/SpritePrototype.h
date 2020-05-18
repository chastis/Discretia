#pragma once

#include <Core/Prototypes/BasePrototype.h>
#include <Core/Utility/SFMLAdapter.h>
#include <Core/Utility/Json.h>
#include <SFML/Graphics.hpp>


class SpritePrototype : public BasePrototype
{
public:
    bool Init(nlohmann::json::iterator nodeIt) override
    {
        if (BasePrototype::Init(nodeIt))
        {
            const nlohmann::json& node = nodeIt.value();
            if (!node.contains("texture")
                ||!node.contains("rect"))
            {
                __debugbreak();
                return false;
            }
            textureSID = node.at("texture").get<std::string>();
            rect = node.at("rect").get<sf::IntRect>();
            return true;
        }
        return false;
    }
    [[nodiscard]] const std::string& getTextureSID() const
    {
        return textureSID;
    }
    [[nodiscard]] const sf::IntRect& getRect() const
    {
        return rect;
    }
protected:
    std::string textureSID;
    sf::IntRect rect;

};

using SpritePrototypes = BasePrototypes<SpritePrototype>;
