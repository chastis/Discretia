#pragma once

#include <Core/Singletons/BaseSingleton.h>
#include <Core/CoreDefs.h>

class CORE_API UIDManager : public BaseSingleton<UIDManager>
{
public:
    void Init() override;
    size_t Register();
private:
    size_t nextUID = 0;
};