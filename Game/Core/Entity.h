#pragma once

#include <Core/Factories/ComponentFactory.h>
#include <Core/EventSystem/EventCaller.h>
#include <Core/Interfaces/UIDInterface.h>
#include <Core/Interfaces/PrototypeableInterface.h>
#include <Core/Prototypes/EntityPrototype.h>
#include <Core/Components/BaseComponent.h>
#include <Core/Utility/Noncopyable.h>
#include <Core/CoreDefs.h>
#include <memory>
#include <vector>

class CORE_API Entity : public Noncopyable,  public PrototypeableInterface<EntityPrototype>, public UIDInterface, public EventCaller
{
public:
    void InitFromPrototype() override;
    void InitEventFunctions() override;

    template<class T>
    T* AddComponent()
    {
        if constexpr (std::is_base_of<BaseComponent, T>::value)
        {
            const auto newBaseComponent = ComponentFactory::GetInstance().CreateComponent(typeid(T));
            return dynamic_cast<T*>(InitComponent(newBaseComponent));
        }
        else
        {
            static_assert(false, "T must inherit BaseComponent!");
        }
        return  nullptr;
    }

    BaseComponent* AddComponent(const std::string& componentType)
    {
        const auto newBaseComponent = ComponentFactory::GetInstance().CreateComponent(componentType);
        return InitComponent(newBaseComponent);
    }

    template<class T>
    void RemoveComponent()
    {
        for (auto it = components.begin(); it != components.end(); ++it)
        {
            if (dynamic_cast<T*>(it->get()))
            {
                it = components.erase(it);
                return;
            }
        }
    }

    template<class T>
    T* GetComponent()
    {
        for (auto& it : components)
        {
            if (T* component = dynamic_cast<T*>(it.get()))
            {
                return component;
            }
        }
        return nullptr;
    }

    void Init();
private:
    std::vector<std::unique_ptr<BaseComponent>> components;

    BaseComponent* InitComponent(BaseComponent* baseComponent)
    {
        std::unique_ptr<BaseComponent> newComponent(baseComponent);
        newComponent->Init(this);
        components.push_back(std::move(newComponent));
        return components.back().get();
    }
};
