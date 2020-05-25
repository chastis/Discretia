#pragma once

#include <Core/CoreDefs.h>

class CORE_API UIDInterface
{
public:
    [[nodiscard]] size_t GetUID() const
    {
        return uid;
    }
protected:
    size_t uid = 0;
};
