#pragma once

#include <Core/Prototypes/BasePrototype.h>
#include <Core/Utility/Json.h>
#include <Core/Consts/Enums.h>
#include <string>
#include <vector>

class RecipePrototype : public BasePrototype
{
public:
    bool Init(nlohmann::json::iterator nodeIt) override
    {
        if (BasePrototype::Init(nodeIt))
        {
            const nlohmann::json& node = nodeIt.value();
            if (!node.contains("elements")
                ||!node.contains("operation")
                ||!node.contains("result"))
            {
                __debugbreak();
                return false;
            }
            elements = node.at("elements").get<std::vector<std::string>>();
            operation = node.at("operation").get<DiscreteOperations>();
            result = nodeIt->at("result").get<std::string>();
            return true;
        }
        return false;
    }
    [[nodiscard]] const std::vector<std::string>& getElements() const
    {
        return elements;
    }
    [[nodiscard]] DiscreteOperations getOperation() const
    {
        return operation;
    }
    [[nodiscard]] const std::string& getResult() const
    {
        return result;
    }
protected:
    std::vector<std::string> elements;
    std::string result;
    DiscreteOperations operation = DiscreteOperations::None;
};

using RecipePrototypes = BasePrototypes<RecipePrototype>;
