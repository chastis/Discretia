#include <Core/Application.h>
#include <Core/EventSystem/Event.h>
#include <Core/Prototypes/ApplicationPrototype.h>
#include <Core/Singletons/UIDManager.h>
#include <Core/Singletons/PrototypeManager.h>
#include <Core/Singletons/AssetManager.h>
#include <Core/Singletons/EntityManager.h>
#include <Core/Components/DrawableComponent.h>
#include <Core/Entity.h>

void Application::InitFromPrototype()
{
    UIDManager::CreateInstance();
    PrototypeManager::CreateInstance();
    AssetManager::CreateInstance();
    EntityManager::CreateInstance();

    UIDManager::GetInstance().Init();
    PrototypeManager::GetInstance().Init();
    AssetManager::GetInstance().Init();
    EntityManager::GetInstance().Init();

    if (!prototype)
    {
        prototype = &ApplicationPrototypes::GetDefault();
    }
    window.create(sf::VideoMode(static_cast<unsigned int>(prototype->getWidth()), static_cast<unsigned int>(prototype->getHeight())), prototype->getTitle());

    InitEventFunctions();
}

void Application::InitEventFunctions()
{
    eventFunctions = EventFunctionHandler<Application>::GetEventFunctions();
    if (eventFunctions->empty()) // not implemented
    {
        auto newEventFunction = [](EventCaller* eventCaller, Event& inEvent)
        {
            auto application = dynamic_cast<Application*>(eventCaller);
            const auto sfEvent = dynamic_cast<SFMLEvent*>(&inEvent);
            if (application && sfEvent && sfEvent->type == sf::Event::EventType::Closed)
            {
                application->window.close();
            }
        };
        eventFunctions->emplace("closing", newEventFunction);
    }
}

bool Application::IsRunning() const
{
    return window.isOpen();
}

void Application::Run()
{
    
    Entity* VPSHENEMY = EntityManager::GetInstance().CreateEntity();
    auto drawableComponent = VPSHENEMY->AddComponent<DrawableComponent>();
    drawableComponent->InitPrototype("vpsh");
    drawableComponent->InitFromPrototype();
    VPSHENEMY->InitFromPrototype();

    EventReceiver* MouseMove = new EventReceiver("move", ChannelEventType::Application, VPSHENEMY);
    eventDispatcher.JoinEvent(MouseMove);

    EventReceiver* CloseApp = new EventReceiver("closing", ChannelEventType::Application, this);
    eventDispatcher.JoinEvent(CloseApp);

}

void Application::Update()
{
    sf::CircleShape shape;
    shape.setRadius(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Event sfEvent;

    while (window.pollEvent(sfEvent))
    {
        SFMLEvent newEvent(sfEvent);
        eventDispatcher.Dispatch(newEvent);
    }

    window.clear();
    for (const auto& entity : EntityManager::GetInstance().GetEntities())
    {
        auto drawableComponent = entity.second->GetComponent<DrawableComponent>();
        if (drawableComponent)
        {
            //drawableComponent.
            window.draw(*drawableComponent);
        }
    }

    window.display();
}
