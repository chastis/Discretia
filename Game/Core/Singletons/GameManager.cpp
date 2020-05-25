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

void GameManager::Init()
{

}
