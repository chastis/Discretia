#include <Core/Application.h>
#include <Core/EventSystem/Event.h>
#include <Core/Prototypes/ApplicationPrototype.h>
#include <Core/Factories/ComponentFactory.h>
#include <Core/Singletons/UIDManager.h>
#include <Core/Singletons/PrototypeManager.h>
#include <Core/Singletons/AssetManager.h>
#include <Core/Singletons/EntityManager.h>
#include <Core/Singletons/GameManager.h>
#include <Core/Singletons/TimeManager.h>
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
    TimeManager::CreateInstance();

    UIDManager::GetInstance().Init();
    PrototypeManager::GetInstance().Init();
    AssetManager::GetInstance().Init();
    EntityManager::GetInstance().Init();
    GameManager::GetInstance().InitFromApplication(this);
    TimeManager::GetInstance().Init();
    // Factories

    ComponentFactory::CreateInstance();
    ComponentFactory::GetInstance().Init();

    if (!prototype)
    {
        prototype = &ApplicationPrototypes::GetDefault();
    }
    window.create(sf::VideoMode(static_cast<unsigned int>(prototype->getWidth()), static_cast<unsigned int>(prototype->getHeight())), prototype->getTitle());
    prevView = { 0, 0, static_cast<float>(prototype->getWidth()), static_cast<float>(prototype->getHeight())};

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
            return false;
        });
        eventFunctions->emplace("resize", [](EventCaller* eventCaller, Event& inEvent)
        {
            auto application = dynamic_cast<Application*>(eventCaller);
            const auto sfEvent = dynamic_cast<SFMLEvent*>(&inEvent);
            if (application && sfEvent && sfEvent->type == sf::Event::EventType::Resized)
            {
                sf::FloatRect newViewport{
                0.f, 0.f,
                static_cast<float>(sfEvent->size.width),
                static_cast<float>(sfEvent->size.height)
                };
                const float preMinLen = static_cast<float>(std::min(application->prevView.width, application->prevView.height));
                const float newScale = static_cast<float>(std::min(newViewport.width / preMinLen, newViewport.height / preMinLen));
                //const float correctScale = newViewport.height/application->GetPrototype().getHeight();
                const float viewportShift = (newViewport.width - newScale * application->prevView.width) / 2;
                //newViewport.left = -viewportShift;
                application->prevView = newViewport;
                application->window.setView(sf::View(newViewport));

                for (auto entity : EntityManager::GetInstance().GetSortedEntities())
                {
                    entity->Scale( { newScale, newScale } );
                    entity->Shift( {viewportShift, 0.f} );
                }
            }
            return false;
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

    Entity* Watermelon = EntityManager::GetInstance().CreateEntity();
    Watermelon->InitPrototype("watermelon");
    Watermelon->InitFromPrototype();
    Watermelon->GetComponent<TransformComponent>()->setPosition(100, 100);

    Entity* Socket = EntityManager::GetInstance().CreateEntity();
    Socket->InitPrototype("socket");
    Socket->InitFromPrototype();
    Socket->GetComponent<TransformComponent>()->setPosition(100, 200);

    Entity* Socket2 = EntityManager::GetInstance().CreateEntity();
    Socket2->InitPrototype("socket");
    Socket2->InitFromPrototype();
    Socket2->GetComponent<TransformComponent>()->setPosition(500, 200);

    Entity* Flex = EntityManager::GetInstance().CreateEntity();
    Flex->InitPrototype("flex");
    Flex->InitFromPrototype();
    Flex->GetComponent<TransformComponent>()->setPosition(300, 500);

    EventReceiver* CloseApp = new EventReceiver("closing", ChannelEvent::Type::Application, this);
    eventDispatcher.JoinEvent(CloseApp);

    EventReceiver* ResizeApp = new EventReceiver("resize", ChannelEvent::Type::Application, this);
    eventDispatcher.JoinEvent(ResizeApp);

}

void Application::Update()
{
    TimeManager::GetInstance().Update();

    {
        sf::Event sfEvent;
        while (window.pollEvent(sfEvent))
        {
            SFMLEvent newEvent(sfEvent);
            eventDispatcher.Dispatch(newEvent);
        }
    }

    EntityManager::GetInstance().UpdateEntities(TimeManager::GetInstance().GetDeltaTime().asSeconds());

    window.clear();

    EntityManager::GetInstance().ActivateEntity();


    for (const auto& render : EntityManager::GetInstance().GetSortedEntities(false))
    {
        auto drawableComponent = render->GetComponent<DrawableComponent>();
        auto transformComponent = render->GetComponent<TransformComponent>();
        if (transformComponent)
        {
            sf::Transform renderTransform = transformComponent->getTransform();
            //renderTransform.scale(scale);
            window.draw(*drawableComponent, renderTransform);
        }
        else
        {
            window.draw(*drawableComponent);
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

sf::Vector2f Application::GeTotalScale() const
{
     const float preMinLen = static_cast<float>(std::min(GetPrototype().getWidth(), GetPrototype().getHeight()));
     const float newScale = static_cast<float>(std::min(window.getSize().x / preMinLen, window.getSize().y/ preMinLen));
     return {newScale, newScale};
}
