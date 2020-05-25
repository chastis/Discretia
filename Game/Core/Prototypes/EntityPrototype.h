#pragma once

#include <Core/Prototypes/BasePrototype.h>
#include <Core/Utility/Json.h>

class EntityPrototype : public BasePrototype
{
public:
    //void InitEventFunctions() override;
    bool Init(nlohmann::json::iterator nodeIt) override
    {
        if (BasePrototype::Init(nodeIt))
        {
            //TODO;;
            return true;
        }
        return false;
    }
protected:
};

using EntityPrototypes = BasePrototypes<EntityPrototype>;
