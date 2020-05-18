#pragma once

#include <Core/Prototypes/BasePrototype.h>
#include <Core/Utility/Json.h>

class TexturePrototype : public BasePrototype
{
public:
    bool Init(nlohmann::json::iterator nodeIt) override
    {
        if (BasePrototype::Init(nodeIt))
        {
            const nlohmann::json& node = nodeIt.value();
            if (!node.contains("path"))
            {
                __debugbreak();
                return false;
            }
            texturePath = node.at("path").get<std::string>();
            return true;
        }
        return false;
    }
    [[nodiscard]] const std::string& getTexturePath() const
    {
        return texturePath;
    }
protected:
    std::string texturePath;
};

using TexturePrototypes = BasePrototypes<TexturePrototype>;
