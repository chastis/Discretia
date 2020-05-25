#pragma once

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
            std::unique_ptr<BaseComponent> newComponent = std::make_unique<T>();
            newComponent->Init(this);
            components.push_back(std::move(newComponent));
            return dynamic_cast<T*>(components.back().get());
        }
        else
        {
            static_assert(false, "T must inherit BaseComponent!");
        }
        return  nullptr;
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
};
