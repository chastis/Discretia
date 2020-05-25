#include <Core/Entity.h>
#include <Core/Singletons/GameManager.h>
#include <Core/Singletons/UIDManager.h>
#include <Core/Components/DrawableComponent.h>
#include <Core/Components/CollisionComponent.h>
#include <Core/Interfaces/PrototypeableInterface.h>

void Entity::InitFromPrototype()
{
    if (!prototype)
    {
        prototype = &EntityPrototypes::GetDefault();
    }

    for (const auto& componentName : prototype->GetComponentNames())
    {
        AddComponent(componentName);
    }

    for (auto& component : components)
    {
        auto prototypeableComponent = dynamic_cast<BasePrototypeableInterface*>(component.get());
        if (prototypeableComponent)
        {
            prototypeableComponent->InitPrototype(prototype->GetSID());
            prototypeableComponent->InitFromPrototype();
        }
    }

    for (const auto& eventParam : prototype->GetEventParams())
    {
        EventReceiver* newEvent = new EventReceiver(eventParam.second, eventParam.first, this);
        GameManager::GetInstance().GetEventDispatcher().JoinEvent(newEvent);
    }

    InitEventFunctions();
}

void Entity::InitEventFunctions()
{
    eventFunctions = EventFunctionHandler<Entity>::GetEventFunctions();
    if (eventFunctions->empty()) // not implemented
    {
        auto newEventFunction = [](EventCaller* eventCaller, Event& inEvent)
        {
            auto entity = dynamic_cast<Entity*>(eventCaller);
            const auto sfEvent = dynamic_cast<SFMLEvent*>(&inEvent);
            if (entity && sfEvent && sfEvent->type == sf::Event::EventType::MouseMoved)
            {
                auto drawableComponent = entity->GetComponent<DrawableComponent>();
                const auto collisionComponent = entity->GetComponent<CollisionComponent>();
                if (drawableComponent && collisionComponent)
                {
                    const sf::Vector2i mousePos = sf::Mouse::getPosition(GameManager::GetInstance().GetWindow());
                    if (collisionComponent->CheckCollision(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    {
                        drawableComponent->setColor(sf::Color::Red);
                    }
                    else
                    {
                        drawableComponent->setColor(sf::Color::White);
                    }
                }
            }
        };
        eventFunctions->emplace("move", newEventFunction);
    }
}

void Entity::Init()
{
    uid = UIDManager::GetInstance().Register();
}

