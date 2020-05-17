#pragma once

#include <Core/Utility/Noncopyable.h>
#include <Core/Utility/Nonmoveable.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>
#include <string>

class Application : public Noncopyable, public Nonmoveable
{
public:
	Application() = default;
	~Application() = default;
	CORE_API void Init();
private:
	sf::RenderWindow window;
};