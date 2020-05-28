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
#include <Core/Singletons/UIManager.h>
#include <Core/Singletons/RecipeManager.h>
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
    UIManager::CreateInstance();
    RecipeManager::CreateInstance();

    UIDManager::GetInstance().Init();
    PrototypeManager::GetInstance().Init();
    AssetManager::GetInstance().Init();
    EntityManager::GetInstance().Init();
    GameManager::GetInstance().InitFromApplication(this);
    TimeManager::GetInstance().Init();
    RecipeManager::GetInstance().Init();

    // Factories
    ComponentFactory::CreateInstance();
    ComponentFactory::GetInstance().Init();

    if (!prototype)
    {
        prototype = &ApplicationPrototypes::GetDefault();
    }
    window.create(sf::VideoMode(static_cast<unsigned int>(prototype->getWidth()), static_cast<unsigned int>(prototype->getHeight())), prototype->getTitle());
    prevView = { 0, 0, static_cast<float>(prototype->getWidth()), static_cast<float>(prototype->getHeight()) };

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

                    if (static_cast<float>(sfEvent->size.width)/static_cast<float>(sfEvent->size.height) < 4.f/3.f)
                    {
                        sfEvent->size.width = static_cast<unsigned int>(4.f * sfEvent->size.height/3.f);
                        application->window.setSize({ static_cast<unsigned int>(4.f * sfEvent->size.height/3.f), sfEvent->size.height });
                    }

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
                    application->totalShift = { (newViewport.width - application->GetPrototype().getWidth() * application->GetTotalScale().x) / 2, 0.f };
                    for (auto entity : EntityManager::GetInstance().GetSortedEntities())
                    {
                        entity->Scale({ newScale, newScale });
                        entity->Shift({ viewportShift, 0.f });
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
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    UIManager::GetInstance().Init();

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

    eventDispatcher.DispatchFutureEvents();

    EntityManager::GetInstance().UpdateEntities(TimeManager::GetInstance().GetDeltaTime().asSeconds());

    //window.clear();

    window.clear(sf::Color(50,50,50));

    window.draw(UIManager::GetInstance().GetBackground());

    // mouse 
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
    for (auto& text : UIManager::GetInstance().GetUITexts())
    {
        window.draw(text);
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

sf::Vector2f Application::GetTotalScale() const
{
    const float preMinLen = static_cast<float>(std::min(GetPrototype().getWidth(), GetPrototype().getHeight()));
    const float newScale = static_cast<float>(std::min(window.getSize().x / preMinLen, window.getSize().y / preMinLen));
    return { newScale, newScale };
}

sf::Vector2f Application::GetTotalShift() const
{
    return totalShift;
}
