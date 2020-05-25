#include <Core/Application.h>
#include <Core/EventSystem/Event.h>
#include <Core/Prototypes/ApplicationPrototype.h>
#include <Core/Factories/ComponentFactory.h>
#include <Core/Singletons/UIDManager.h>
#include <Core/Singletons/PrototypeManager.h>
#include <Core/Singletons/AssetManager.h>
#include <Core/Singletons/EntityManager.h>
#include <Core/Singletons/GameManager.h>
#include <Core/Components/DrawableComponent.h>
#include <Core/Components/CollisionComponent.h>
#include <Core/Components/TransformComponent.h>
#include <Core/Entity.h>

void Application::InitFromPrototype()
{
    // Singletons

    UIDManager::CreateInstance();
    PrototypeManager::CreateInstance();
    AssetManager::CreateInstance();
    EntityManager::CreateInstance();
    GameManager::CreateInstance();

    UIDManager::GetInstance().Init();
    PrototypeManager::GetInstance().Init();
    AssetManager::GetInstance().Init();
    EntityManager::GetInstance().Init();
    GameManager::GetInstance().InitFromApplication(this);

    // Factories

    ComponentFactory::CreateInstance();
    ComponentFactory::GetInstance().Init();

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
        eventFunctions->emplace("closing", [](EventCaller* eventCaller, Event& inEvent)
        {
            auto application = dynamic_cast<Application*>(eventCaller);
            const auto sfEvent = dynamic_cast<SFMLEvent*>(&inEvent);
            if (application && sfEvent && sfEvent->type == sf::Event::EventType::Closed)
            {
                application->window.close();
            }
        });
        eventFunctions->emplace("resize", [](EventCaller* eventCaller, Event& inEvent)
        {
            auto application = dynamic_cast<Application*>(eventCaller);
            const auto sfEvent = dynamic_cast<SFMLEvent*>(&inEvent);
            if (application && sfEvent && sfEvent->type == sf::Event::EventType::Resized)
            {
                const sf::FloatRect newViewport{
                0.f, 0.f,
                static_cast<float>(sfEvent->size.width),
                static_cast<float>(sfEvent->size.height)
                };

                application->window.setView(sf::View(newViewport));
            }
        });
    }
}

bool Application::IsRunning() const
{
    return window.isOpen();
}

void Application::Run()
{
    Entity* VPSHENEMY = EntityManager::GetInstance().CreateEntity();
    VPSHENEMY->InitPrototype("vpsh");
    VPSHENEMY->InitFromPrototype();

    /*auto drawableComponent = VPSHENEMY->AddComponent<DrawableComponent>();
    drawableComponent->InitPrototype("vpsh");
    drawableComponent->InitFromPrototype();

    auto transformComponent = VPSHENEMY->AddComponent<TransformComponent>();
    transformComponent->setPosition(100, 100);
    transformComponent->scale(0.5, 0.5);

    auto collisionComponent = VPSHENEMY->AddComponent<BoxCollisionComponent>();
    collisionComponent->InitFromDrawable();*/

    

    /*EventReceiver* MouseMove = new EventReceiver("move", ChannelEventType::Application, VPSHENEMY);
    eventDispatcher.JoinEvent(MouseMove);*/

    EventReceiver* CloseApp = new EventReceiver("closing", ChannelEventType::Application, this);
    eventDispatcher.JoinEvent(CloseApp);

    EventReceiver* ResizeApp = new EventReceiver("resize", ChannelEventType::Application, this);
    eventDispatcher.JoinEvent(ResizeApp);

}

void Application::Update()
{
    {
        sf::Event sfEvent;
        while (window.pollEvent(sfEvent))
        {
            SFMLEvent newEvent(sfEvent);
            eventDispatcher.Dispatch(newEvent);
        }
    }

    window.clear();
    for (const auto& entity : EntityManager::GetInstance().GetEntities())
    {
        auto drawableComponent = entity.second->GetComponent<DrawableComponent>();
        if (drawableComponent)
        {
            auto transformComponent = entity.second->GetComponent<TransformComponent>();
            if (transformComponent)
            {
                window.draw(*drawableComponent, transformComponent->getTransform());
            }
            else
            {
                window.draw(*drawableComponent);
            }
        }
    }
    window.display();
}

EventDispatcher& Application::GetEventDispatcher()
{
    return eventDispatcher;
}

const sf::RenderWindow& Application::GetWindow() const
{
    return window;
}
