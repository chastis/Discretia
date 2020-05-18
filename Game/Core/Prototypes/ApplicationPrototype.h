#pragma once

#include <Core/Prototypes/BasePrototype.h>
#include <Core/Utility/Json.h>

class ApplicationPrototype : public BasePrototype
{
public:
    bool Init(nlohmann::json::iterator nodeIt) override
    {
        if (BasePrototype::Init(nodeIt))
        {
            const nlohmann::json& node = nodeIt.value();
            if (!node.contains("title")
                || !node.contains("height")
                || !node.contains("width"))
            {
                __debugbreak();
                return false;
            }
            title = node.at("title").get<std::string>();
            height = node.at("height").get<size_t>();
            width = node.at("width").get<size_t>();
            return true;
        }
        return false;
    }
    [[nodiscard]] const std::string& getTitle() const
    {
        return title;
    }
    [[nodiscard]] size_t getHeight() const
    {
        return height;
    }
    [[nodiscard]] size_t getWidth() const
    {
        return width;
    }
protected:
    std::string title;
    size_t height = 0;
    size_t width = 0;
};

using ApplicationPrototypes = BasePrototypes<ApplicationPrototype>;
