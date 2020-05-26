#pragma once

#include <Core/Singletons/BaseSingleton.h>
#include <Core/Prototypes/BasePrototype.h>
#include <Core/Consts/Enums.h>
#include <Core/CoreDefs.h>

#include <vector>
#include <map>

class CORE_API UIManager : public BaseSingleton<UIManager>
{
public:
    void Init() override;
private:
    //std::map<std::vector<const BasePrototype*> all
};