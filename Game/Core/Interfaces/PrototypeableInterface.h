#pragma once

#include <Core/Prototypes/BasePrototype.h>
#include <Core/CoreDefs.h>
#include <string>

template <class T>
class CORE_API PrototypeableInterface
{
public:
    virtual ~PrototypeableInterface() = default;
    virtual void InitFromPrototype() = 0;
    void InitPrototype(size_t prototypeID)
    {
        prototype = &BasePrototypes<T>::Get(prototypeID);
    }
    void InitPrototype(const std::string& prototypeSID)
    {
        prototype = &BasePrototypes<T>::Get(prototypeSID);
    }
    [[nodiscard]] const BasePrototype* GetBasePrototype() const
    {
        return dynamic_cast<const BasePrototype*>(prototype);
    }
    [[nodiscard]] T& GetPrototype() const
    {
        if (prototype)
        {
            return *prototype;
        }
        return BasePrototypes<T>::GetDefault();
    }
protected:
    const T* prototype = nullptr;
};