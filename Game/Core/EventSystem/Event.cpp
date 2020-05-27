#include <Core/EventSystem/Event.h>
#include <Core/Consts/Misc.h>
#include <Core/Singletons/EntityManager.h>
#include <Core/Singletons/RecipeManager.h>
#include <Core/Singletons/UIManager.h>
#include <Core/Prototypes/EntityPrototype.h>
#include <Core/Singletons/GameManager.h>
#include <Core/Components/TransformComponent.h>
#include <Core/Components/CollisionComponent.h>
#include <Core/Entity.h>

SFMLEvent::SFMLEvent(sf::Event inEvent)
{
    auto thisSFML = dynamic_cast<sf::Event*>(this);
    *thisSFML = inEvent;
    channelType = Misc::GetChannelTypeFromSFML(inEvent.type);
}

CreateEntityEvent::CreateEntityEvent(const RecipePrototype* recipe, sf::Vector2f location) : entityRecipe(recipe), entityLocation(location)
{
    channelType = ChannelEvent::Custom;
}

void CreateEntityEvent::AddEntityForDelete(Entity* entity)
{
    entitiesForDelete.push_back(entity);
}

std::string CreateEntityEvent::GetResult() const
{
    return entityRecipe->getResult();
}

Entity* CreateEntityEvent::CreateEntity()
{
    Entity* newEntity = EntityManager::GetInstance().CreateEntity();
    newEntity->InitPrototype(entityRecipe->getResult());
    newEntity->InitFromPrototype();

    if (!RecipeManager::GetInstance().IsKnownItem("ui_" + entityRecipe->getResult()))
    {
        RecipeManager::GetInstance().AddKnownItem("ui_" + entityRecipe->getResult());
        UIManager::GetInstance().ChangeVisibleItemTypes(EntityPrototypes::Get("ui_" + entityRecipe->getResult()).GetItemType());
    }

    newEntity->GetComponent<TransformComponent>()->setPosition(entityLocation - newEntity->GetComponent<CollisionComponent>()->GetPropertyCenter());

    for (const auto attach : entitiesForDelete)
    {
        GameManager::GetInstance().GetEventDispatcher().LeaveChannel(ChannelEvent::Type::All, attach->GetUID());
        EntityManager::GetInstance().RemoveEntityByUID(attach->GetUID());
    }

    return  newEntity;
}

std::vector<Entity*> CreateEntityEvent::GetDeletedEntities()
{
    return entitiesForDelete;
}
