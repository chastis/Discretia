#include <Core/Singletons/TimeManager.h>

void TimeManager::Init()
{
    RestartGameTimer();
}

void TimeManager::Update()
{
    deltaTime = frameTimer.getElapsedTime();
    frameTimer.restart();
}

void TimeManager::RestartGameTimer()
{
    gameTimer.restart();
}

sf::Time TimeManager::GetGameTime() const
{
    return gameTimer.getElapsedTime();
}

sf::Time TimeManager::GetDeltaTime() const
{
    return deltaTime;
}

