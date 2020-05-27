#include <Core/Singletons/GameManager.h>
#include <Core/Application.h>

void GameManager::InitFromApplication(Application* inApplication)
{
    application = inApplication;
    Init();
}

EventDispatcher& GameManager::GetEventDispatcher() const
{
    return application->GetEventDispatcher();
}

const sf::RenderWindow& GameManager::GetWindow() const
{
    return application->GetWindow();
}

sf::Vector2f GameManager::GetTotalScale() const
{
    return application->GetTotalScale();
}

sf::Vector2f GameManager::GetTotalShift() const
{
    return application->GetTotalShift();
}

void GameManager::Init()
{

}
