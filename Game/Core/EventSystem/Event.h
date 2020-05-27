#pragma once

#include <Core/Consts/Enums.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>

class CORE_API Event
{
public:
    virtual ~Event() = default;
    ChannelEvent::Type channelType = ChannelEvent::Type::None;
};

class CORE_API SFMLEvent : public Event, public sf::Event
{
public:
    SFMLEvent(sf::Event inEvent);
};

class Entity;
class RecipePrototype;

class CreateEntityEvent : public Event
{
public:
    CreateEntityEvent(const RecipePrototype* recipe, sf::Vector2f location);
    void AddEntityForDelete(Entity* entity);
    [[nodiscard]] std::string GetResult() const;
    Entity* CreateEntity();
    std::vector<Entity*> GetDeletedEntities();
protected:
    const RecipePrototype* entityRecipe;
    sf::Vector2f entityLocation;
    std::vector<Entity*> entitiesForDelete;
};