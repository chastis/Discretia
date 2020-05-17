#pragma once

#include <Core/Utility/Noncopyable.h>
#include <Core/Utility/Nonmoveable.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>

class TimeManager : public Noncopyable, public Nonmoveable
{
public:
    CORE_API static TimeManager Instance;
    CORE_API void Update();
    CORE_API void RestartGameTimer();
    [[nodiscard]] CORE_API sf::Time GetGameTime() const;
    [[nodiscard]] CORE_API sf::Time GetDeltaTime() const;

private:
    TimeManager() = default;
    ~TimeManager() = default;
    sf::Clock gameTimer;
    sf::Clock frameTimer;
    sf::Time deltaTime;
};

