#pragma once
#include <Core/Components/BaseComponent.h>
#include <Core/Utility/Noncopyable.h>
#include <Core/CoreDefs.h>
#include <memory>
#include <vector>

class CORE_API Entity : public Noncopyable
{
public:

    template<class T>
    void AddComponent()
    {
        if constexpr (std::is_base_of<BaseComponent, T>::value)
        {
            std::unique_ptr<BaseComponent> newComponent = std::make_unique<T>();
            newComponent->Init(this);
            components.push_back(std::move(newComponent));
        }
        else
        {
            static_assert(false, "T must inherit BaseComponent!");
        }
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
        for (auto it = components.begin(); it != components.end(); ++it)
        {
            if (T* component = dynamic_cast<T*>(it->get()))
            {
                return component;
            }
        }
        return nullptr;
    }

    void Init();
    [[nodiscard]] size_t GetUID() const;
private:
    std::vector<std::unique_ptr<BaseComponent>> components;
    size_t uid = 0;
};
