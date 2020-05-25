#pragma once

#include <Core/Prototypes/BasePrototype.h>
#include <Core/Utility/Json.h>

class CollisionPrototype : public BasePrototype
{
public:
    bool Init(nlohmann::json::iterator nodeIt) override
    {
        if (BasePrototype::Init(nodeIt))
        {
            const nlohmann::json& node = nodeIt.value();
            if (node.contains("useDrawable"))
            {
                useDrawable = node.at("useDrawable").get<bool>();
            }
            return true;
        }
        return false;
    }
    [[nodiscard]] bool UseDrawable() const
    {
        return useDrawable;
    }
protected:
    bool useDrawable = true;
};

using CollisionPrototypes = BasePrototypes<CollisionPrototype>;
