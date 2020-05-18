#pragma once

#include <Core/Singletons/BaseSingleton.h>
#include <Core/CoreDefs.h>

class CORE_API PrototypeManager : public BaseSingleton<PrototypeManager>
{
public:
    void Init() override;
};
