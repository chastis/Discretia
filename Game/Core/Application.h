#pragma once

#include <Core/Utility/Noncopyable.h>
#include <Core/Utility/Nonmoveable.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>

class CORE_API Application : public Noncopyable, public Nonmoveable
{
public:
    Application() = default;
    ~Application() = default;
    bool IsRunning() const;
    void Init();
    void Update();
private:
    sf::RenderWindow window;
};