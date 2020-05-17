#pragma once

#include <Core/Utility/Noncopyable.h>
#include <Core/Utility/Nonmoveable.h>
#include <Core/CoreDefs.h>

class UIDManager : public Noncopyable, public Nonmoveable
{
public:
    CORE_API static UIDManager Instance;
    CORE_API size_t Register();
private:
    UIDManager() = default;
    ~UIDManager() = default;
    size_t nextUID = 0;
};