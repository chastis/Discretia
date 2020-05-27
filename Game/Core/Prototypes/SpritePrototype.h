#pragma once

#include <Core/Prototypes/BasePrototype.h>
#include <Core/Utility/SFMLAdapter.h>
#include <Core/Utility/Json.h>
#include <SFML/Graphics.hpp>
#include <optional>

class SpritePrototype : public BasePrototype
{
public:
    bool Init(nlohmann::json::iterator nodeIt) override
    {
        if (BasePrototype::Init(nodeIt))
        {
            const nlohmann::json& node = nodeIt.value();
            if (!node.contains("texture")
                ||(!node.contains("scale") && !node.contains("scale_to")))
            {
                __debugbreak();
                return false;
            }
            textureSID = node.at("texture").get<std::string>();
            if (node.contains("rect"))
            {
                rect = node.at("rect").get<sf::IntRect>();
            }
            if (node.contains("z_index"))
            {
                zIndex = node.at("z_index").get<size_t>();
            }
            if (node.contains("scale"))
            {
                scale = node.at("scale").get<sf::Vector2f>();
            }
            else
            {
                useScaleTo = true;
                scale = node.at("scale_to").get<sf::Vector2f>();
            }
            
            return true;
        }
        return false;
    }
    [[nodiscard]] const std::string& getTextureSID() const
    {
        return textureSID;
    }
    [[nodiscard]] const std::optional<sf::IntRect>& getRect() const
    {
        return rect;
    }
    [[nodiscard]] const sf::Vector2f& getScale() const
    {
        return scale;
    }
    [[nodiscard]] size_t GetZIndex() const
    {
        return zIndex;
    }
    [[nodiscard]] bool UseScaleTo() const
    {
        return useScaleTo;
    }
protected:
    std::string textureSID;
     
    sf::Vector2f scale;
    std::optional<sf::IntRect> rect;

    size_t zIndex = 1;
    bool useScaleTo = false;

};

using SpritePrototypes = BasePrototypes<SpritePrototype>;
