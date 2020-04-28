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
			Components.push_back(std::move(newComponent));
		}
		else
		{
			static_assert(false, "T must inherit BaseComponent!");
		}
	}

	template<class T>
	void RemoveComponent()
	{
		for (auto it = Components.begin(); it != Components.end(); ++it)
		{
			if (dynamic_cast<T*>(it->get()))
			{
				it = Components.erase(it);
				return;
			}
		}
	}

	template<class T>
	T* GetComponent()
	{
		for (auto it = Components.begin(); it != Components.end(); ++it)
		{
			if (T* component = dynamic_cast<T*>(it->get()))
			{
				return component;
			}
		}
		return nullptr;
	}

	void Init();

private:
	std::vector<std::unique_ptr<BaseComponent>> Components;
	size_t UID = 0;
};
