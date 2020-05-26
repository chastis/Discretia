#include <Core/Entity.h>
#include <Core/Singletons/GameManager.h>
#include <Core/Singletons/UIDManager.h>
#include <Core/Singletons/EntityManager.h>
#include <Core/Singletons/RecipeManager.h>
#include <Core/Components/TransformComponent.h>
#include <Core/Components/DrawableComponent.h>
#include <Core/Components/CollisionComponent.h>
#include <Core/Components/AttachComponent.h>
#include <Core/Interfaces/PrototypeableInterface.h>
#include <iostream>

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
        const auto newEvent = new EventReceiver(eventParam.second, eventParam.first, this);
        GameManager::GetInstance().GetEventDispatcher().JoinEvent(newEvent);
    }

    InitEventFunctions();

    Scale(GameManager::GetInstance().GeTotalScale());
}

void Entity::InitEventFunctions()
{
    eventFunctions = EventFunctionHandler<Entity>::GetEventFunctions();
    if (eventFunctions->empty()) // not implemented
    {
        eventFunctions->emplace("obj_hoover", [](EventCaller* eventCaller, Event& inEvent)
            {
                auto entity = dynamic_cast<Entity*>(eventCaller);
                const auto sfEvent = dynamic_cast<SFMLEvent*>(&inEvent);
                if (entity && sfEvent && sfEvent->type == sf::Event::EventType::MouseMoved)
                {
                    auto drawableComponent = entity->GetComponent<DrawableComponent>();
                    if (drawableComponent)
                    {
                        if (entity->bActive)
                        {
                            if (drawableComponent->getColor() == sf::Color::White)
                            {
                                drawableComponent->setColor(sf::Color::Yellow);
                            }
                        }
                        else
                        {
                            drawableComponent->setColor(sf::Color::White);
                        }
                    }
                }
                return false;
            });
        eventFunctions->emplace("obj_click", [](EventCaller* eventCaller, Event& inEvent)
            {
                auto entity = dynamic_cast<Entity*>(eventCaller);
                const auto sfEvent = dynamic_cast<SFMLEvent*>(&inEvent);
                if (entity && sfEvent)
                {
                    if (sfEvent->type == sf::Event::EventType::MouseButtonPressed)
                    {
                        auto drawableComponent = entity->GetComponent<DrawableComponent>();
                        const auto transformComponent = entity->GetComponent<TransformComponent>();
                        if (drawableComponent && transformComponent)
                        {
                            if (entity->bActive)
                            {
                                drawableComponent->zIndex = DrawableComponent::GetNewMaxIndexZ();
                                drawableComponent->setColor(sf::Color::Red);

                                const auto newEvent = new EventReceiver("obj_move", ChannelEvent::Type::Mouse, eventCaller);
                                GameManager::GetInstance().GetEventDispatcher().JoinEvent(newEvent);

                                const auto mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(GameManager::GetInstance().GetWindow()));
                                const auto position = transformComponent->getPosition() - transformComponent->getOrigin();
                                const sf::Vector2f newOrigin = { mousePos.x - position.x, mousePos.y - position.y };
                                transformComponent->setOrigin(newOrigin);
                                transformComponent->setPosition(mousePos);
                            }
                        }
                    }
                    else if (sfEvent->type == sf::Event::EventType::MouseButtonReleased)
                    {
                        auto drawableComponent = entity->GetComponent<DrawableComponent>();
                        if (drawableComponent)
                        {
                            if (entity->bActive)
                            {
                                GameManager::GetInstance().GetEventDispatcher().RemoveEvent(entity, "obj_move");
                                drawableComponent->setColor(sf::Color::Yellow);

                                // this stopped moving attached item, i don't remember why i add it
                                //const auto transformComponent = entity->GetComponent<TransformComponent>();
                                //if (transformComponent && transformComponent->moving)
                                //{
                                //    transformComponent->moving = false;
                                //}
                            }
                        }
                    }
                }
                return false;
            });
        eventFunctions->emplace("obj_move", [](EventCaller* eventCaller, Event& inEvent)
            {
                auto entity = dynamic_cast<Entity*>(eventCaller);
                const auto sfEvent = dynamic_cast<SFMLEvent*>(&inEvent);
                if (entity && sfEvent)
                {
                    if (entity->bActive)
                    {
                        const auto transformComponent = entity->GetComponent<TransformComponent>();
                        if (transformComponent)
                        {
                            const auto mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(GameManager::GetInstance().GetWindow()));
                            transformComponent->setPosition(mousePos);
                        }
                    }
                    else
                    {
                        // THIS IS HAS TO NEVER HAPPEN BUT FUCKING NO
                        GameManager::GetInstance().GetEventDispatcher().RemoveEvent(entity, "obj_move");
                    }
                }
                return false;
            });

        eventFunctions->emplace("socket_hoover", [](EventCaller* eventCaller, Event& inEvent)
            {
                auto entity = dynamic_cast<Entity*>(eventCaller);
                const auto sfEvent = dynamic_cast<SFMLEvent*>(&inEvent);
                if (entity && sfEvent && sfEvent->type == sf::Event::EventType::MouseButtonReleased)
                {
                    Entity* activeEntity = EntityManager::GetInstance().GetActiveEntity(false);
                    if (activeEntity && activeEntity->GetUID() != entity->GetUID())
                    {
                        const auto activeEntityCollisionComponent = activeEntity->GetComponent<CollisionComponent>();
                        const auto collisionComponent = entity->GetComponent<CollisionComponent>();
                        const auto activeEntityTransformComponent = activeEntity->GetComponent<TransformComponent>();
                        auto attachComponent = entity->GetComponent<AttachComponent>();
                        if (collisionComponent && activeEntityTransformComponent && activeEntityCollisionComponent && attachComponent)
                        {
                            if (activeEntityCollisionComponent->CheckCollision(collisionComponent) && attachComponent->TryAttach(activeEntity))
                            {
                                const auto propertyDesiredLocation = collisionComponent->GetPropertyCenterWorldSpace() - activeEntityCollisionComponent->GetPropertyCenter();
                                activeEntityTransformComponent->MoveTo(propertyDesiredLocation);
                            }

                        }
                    }
                }
                return false;
            });

        eventFunctions->emplace("button_hoover", [](EventCaller* eventCaller, Event& inEvent)
            {
                auto entity = dynamic_cast<Entity*>(eventCaller);
                const auto sfEvent = dynamic_cast<SFMLEvent*>(&inEvent);
                if (entity && sfEvent && sfEvent->type == sf::Event::EventType::MouseMoved)
                {
                    auto drawableComponent = entity->GetComponent<DrawableComponent>();
                    if (drawableComponent)
                    {
                        if (entity->bActive)
                        {
                            if (drawableComponent->getColor() == sf::Color::White)
                            {
                                drawableComponent->setColor(sf::Color::Magenta);
                            }
                        }
                        else
                        {
                            drawableComponent->setColor(sf::Color::White);
                        }
                    }
                }
                return false;
            });
        eventFunctions->emplace("button_click", [](EventCaller* eventCaller, Event& inEvent)
            {
                auto entity = dynamic_cast<Entity*>(eventCaller);
                const auto sfEvent = dynamic_cast<SFMLEvent*>(&inEvent);
                if (entity && sfEvent)
                {
                    if (sfEvent->type == sf::Event::EventType::MouseButtonPressed)
                    {
                        const auto transformComponent = entity->GetComponent<TransformComponent>();
                        if (transformComponent)
                        {
                            if (entity->bActive)
                            {
                                std::vector<Entity*> sockets = EntityManager::GetInstance().GetEntitiesBtySID("socket");
                                std::vector<Entity*> attached;
                                for (const auto& socket : sockets)
                                {
                                    if (!socket) break;
                                    auto attachComponent = socket->GetComponent<AttachComponent>();
                                    if (!attachComponent) break;
                                    Entity* attachedEntity = attachComponent->GetAttached();
                                    if (attachedEntity)
                                        attached.push_back(attachedEntity);
                                }
                                std::vector<std::string> attachedSIDs;
                                attachedSIDs.reserve(attached.size());
                                for (const auto& attach : attached)
                                {
                                    attachedSIDs.push_back(attach->GetPrototype().GetSID());
                                }

                                const RecipePrototype* newEntityPrototype = RecipeManager::GetInstance().CheckExistRecipe(attachedSIDs, DiscreteOperations::Union);

                                if (newEntityPrototype)
                                {
                                    Entity* newEntity = EntityManager::GetInstance().CreateEntity();
                                    newEntity->InitPrototype(newEntityPrototype->GetSID());
                                    newEntity->InitFromPrototype();
                                    const auto newEntityPos = transformComponent->getPosition() + sf::Vector2f(0,-300 * GameManager::GetInstance().GeTotalScale().x);
                                    newEntity->GetComponent<TransformComponent>()->setPosition(newEntityPos);

                                    for (const auto& attach : attached)
                                    {
                                        GameManager::GetInstance().GetEventDispatcher().LeaveChannel(ChannelEvent::Type::All, attach->GetUID());
                                        EntityManager::GetInstance().RemoveEntityByUID(attach->GetUID());
                                    }
                                }
                            }
                        }
                    }
                }
                return false;
            });
    }
}

void Entity::Init()
{
    uid = UIDManager::GetInstance().Register();
}

void Entity::Update(float deltaTime)
{
    for (auto& component : components)
    {
        component->Update(deltaTime);
    }
}

void Entity::Scale(sf::Vector2f scale)
{
    auto transformComponent = GetComponent<TransformComponent>();
    if (transformComponent)
    {
        const auto pos = transformComponent->getPosition();
        transformComponent->setPosition(pos.x * scale.x, pos.y * scale.y);
    }
    auto drawableComponent = GetComponent<DrawableComponent>();
    if (drawableComponent)
    {
        drawableComponent->scale(scale);
    }
    auto collisionComponent = GetComponent<CollisionComponent>();
    if (collisionComponent)
    {
        collisionComponent->scale(scale);
    }
}

void Entity::Shift(sf::Vector2f shift)
{
    // todo : gamno ili ne?
    auto transformComponent = GetComponent<TransformComponent>();
    if (transformComponent)
    {
        const auto pos = transformComponent->getPosition();
        transformComponent->setPosition(pos.x + shift.x, pos.y + shift.y);
    }
}

