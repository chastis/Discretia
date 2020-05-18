#pragma once

#include <SFML/Graphics.hpp>
#include <Core/Utility/Json.h>

namespace sf
{
    // IntRect

    inline void to_json(nlohmann::json& j, const sf::IntRect& rect) 
    {
        j = nlohmann::json{{"left", rect.left}, {"top", rect.top}, {"height", rect.height}, {"width", rect.width}};
    }

    inline void from_json(const nlohmann::json& j, sf::IntRect& rect) 
    {
        j.at("left").get_to(rect.left);
        j.at("top").get_to(rect.top);
        j.at("height").get_to(rect.height);
        j.at("width").get_to(rect.width);
    }

    // Vector2f

    inline void to_json(nlohmann::json& j, const sf::Vector2f& vec) 
    {
        j = nlohmann::json{{"x", vec.x}, {"y", vec.y}};
    }

    inline void from_json(const nlohmann::json& j, sf::Vector2f& vec) 
    {
        j.at("x").get_to(vec.x);
        j.at("y").get_to(vec.y);
    }

} // namespace sf