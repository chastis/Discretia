#pragma once

#include <Core/Prototypes/BasePrototype.h>
#include <Core/CoreDefs.h>
#include <string>

class CORE_API BasePrototypeableInterface
{
public:
    virtual ~BasePrototypeableInterface() = default;
    virtual void InitFromPrototype() = 0;
    virtual void InitPrototype(size_t prototypeID) = 0;
    virtual void InitPrototype(const std::string& prototypeSID) = 0;
    [[nodiscard]] virtual const BasePrototype* GetBasePrototype() const = 0;
};

template <class T>
class CORE_API PrototypeableInterface : public BasePrototypeableInterface
{
public:
    virtual ~PrototypeableInterface() = default;
    //virtual void InitFromPrototype() = 0;
    void InitPrototype(size_t prototypeID) override
    {
        prototype = &BasePrototypes<T>::Get(prototypeID);
    }
    void InitPrototype(const std::string& prototypeSID) override
    {
        prototype = &BasePrototypes<T>::Get(prototypeSID);
    }
    [[nodiscard]] const BasePrototype* GetBasePrototype() const override
    {
        return dynamic_cast<const BasePrototype*>(prototype);
    }
    [[nodiscard]] const T& GetPrototype() const
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