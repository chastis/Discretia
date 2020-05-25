#include <Core/Entity.h>
#include <Core/Singletons/UIDManager.h>
#include <Core/Components/DrawableComponent.h>

void Entity::InitFromPrototype()
{
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
                DrawableComponent* drawableComponent = entity->GetComponent<DrawableComponent>();
                if (drawableComponent)
                {
                    const sf::Vector2i mousePos = sf::Mouse::getPosition();
                    const sf::FloatRect drawBounds = drawableComponent->getGlobalBounds();
                    if (drawBounds.contains(mousePos.x, mousePos.y))
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

