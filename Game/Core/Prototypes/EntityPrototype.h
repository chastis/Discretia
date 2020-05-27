#pragma once

#include <Core/Prototypes/BasePrototype.h>
#include <Core/Consts/Enums.h>
#include <Core/Utility/Json.h>
#include <vector>
#include <string>
#include <optional>

class EntityPrototype : public BasePrototype
{
public:
    bool Init(nlohmann::json::iterator nodeIt) override
    {
        if (BasePrototype::Init(nodeIt))
        {
            const nlohmann::json& node = nodeIt.value();

            if (node.contains("components"))
                componentNames = node.at("components").get<std::vector<std::string>>();
            if (node.contains("events"))
                eventParams = node.at("events").get<std::vector<std::pair<ChannelEvent::Type, std::string>>>();
            if (node.contains("type"))
                itemType = node.at("type").get<EntityTypes>();
            return true;
        }
        return false;
    }
    [[nodiscard]] const std::vector<std::string>& GetComponentNames() const
    {
        return componentNames;
    }
    [[nodiscard]] const std::vector<std::pair<ChannelEvent::Type, std::string>>& GetEventParams() const
    {
        return eventParams;
    }
    [[nodiscard]] EntityTypes GetItemType() const
    {
        return itemType;
    }
protected:
    EntityTypes itemType = EntityTypes::Core;
    std::vector<std::string> componentNames;
    std::vector<std::pair<ChannelEvent::Type, std::string>> eventParams;
};

using EntityPrototypes = BasePrototypes<EntityPrototype>;
