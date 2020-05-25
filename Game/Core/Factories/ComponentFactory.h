#pragma once

#include <Core/Singletons/BaseSingleton.h>
#include <Core/CoreDefs.h>
#include <unordered_map>
#include <functional>
#include <typeinfo>

using TypeInfoRef = std::reference_wrapper<const std::type_info>;

class BaseComponent;

class CORE_API ComponentFactory : public BaseSingleton<ComponentFactory>
{
public:
    void Init() override;
    BaseComponent* CreateComponent(TypeInfoRef type);
    BaseComponent* CreateComponent(const std::string& typeName);

private:
    struct Hasher
    {
        std::size_t operator()(TypeInfoRef code) const
        {
            return code.get().hash_code();
        }
    };
    struct EqualTo
    {
        bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const
        {
            return lhs.get() == rhs.get();
        }
    };
    std::unordered_map<TypeInfoRef, std::function<BaseComponent*()>, Hasher, EqualTo> creatorComponents;
};