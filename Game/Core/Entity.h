#pragma once
#include <Core/Components/BaseComponent.h>
#include <Core/Utility/Noncopyable.h>
#include <Core/CoreDefs.h>
#include <vector>
#include <memory>

class CORE_DLL Entity : public Noncopyable
{
public:

	template<class T>
	void AddComponent()
	{
		if constexpr (std::is_base_of<BaseComponent, T>::value)
		{
			std::unique_ptr<BaseComponent> newComponent = std::make_unique<T>();
			newComponent->Init(this);
			Components.push_back(newComponent);
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

	void Init();

private:
	std::vector<std::unique_ptr<BaseComponent>> Components;
	size_t UID = 0;
};