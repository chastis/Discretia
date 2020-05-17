#pragma once

#include <Core/Utility/Noncopyable.h>
#include <Core/Utility/Nonmoveable.h>
#include <Core/CoreDefs.h>
#include <vector>
#include <memory>

template <class T>
class BasePrototypes;

class BasePrototype;

class PrototypeManager : public Noncopyable, public Nonmoveable
{
public:
    CORE_API void Init();
    CORE_API static PrototypeManager Instance;
private:
    PrototypeManager() = default;
    ~PrototypeManager() = default;
    std::vector<std::unique_ptr<BasePrototypes<BasePrototype>>> prototypes;
};
