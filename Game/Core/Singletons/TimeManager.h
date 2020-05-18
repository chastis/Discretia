#pragma once

#include <Core/Singletons/BaseSingleton.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>

class TimeManager : public BaseSingleton<TimeManager>
{
public:
    void Init() override;
    void Update();
    void RestartGameTimer();
    [[nodiscard]] CORE_API sf::Time GetGameTime() const;
    [[nodiscard]] CORE_API sf::Time GetDeltaTime() const;

private:
    sf::Clock gameTimer;
    sf::Clock frameTimer;
    sf::Time deltaTime;
};

