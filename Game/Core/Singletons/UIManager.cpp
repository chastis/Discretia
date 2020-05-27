#include <Core/Singletons/UIManager.h>
#include <Core/Singletons/EntityManager.h>
#include <Core/Singletons/RecipeManager.h>
#include <Core/Singletons/GameManager.h>
#include <Core/Singletons/AssetManager.h>
#include <Core/Prototypes/EntityPrototype.h>
#include <Core/Components/TransformComponent.h>
#include <Core/Components/CollisionComponent.h>
#include <Core/Components/DrawableComponent.h>
#include <Core/Entity.h>
#include <string>
#include <vector>
#include <SFML/Graphics/Text.hpp>


void UIManager::Init()
{
    /*for (size_t i = 0; i < EntityPrototypes::Size(); ++i)
    {
        const EntityPrototype& entityPrototype = EntityPrototypes::Get(i);
        if (entityPrototype.GetItemType() != EntityTypes::Core)
        {
            allItems[entityPrototype.GetItemType()].push_back(&entityPrototype);
        }
    }*/

    // buttons

    Entity* Flex = EntityManager::GetInstance().CreateEntity();
    Flex->InitPrototype("flex");
    Flex->InitFromPrototype();
    Flex->GetComponent<TransformComponent>()->setPosition(400, 410);

    Entity* buttonUp = EntityManager::GetInstance().CreateEntity();
    buttonUp->InitPrototype("button_up");
    buttonUp->InitFromPrototype();
    buttonUp->GetComponent<TransformComponent>()->setPosition(100, 10);

    Entity* buttonDown = EntityManager::GetInstance().CreateEntity();
    buttonDown->InitPrototype("button_down");
    buttonDown->InitFromPrototype();
    buttonDown->GetComponent<TransformComponent>()->setPosition(100, 550);

    // groups
    std::vector<std::string> groups = { "group_a", "group_b" };
    const auto leftShift = 10.f;
    const auto deltaShiftY = 10.f;
    auto currentDeltaShiftY = 60.f;
    for (const auto& groupName : groups)
    {
        Entity* group = EntityManager::GetInstance().CreateEntity();
        group->InitPrototype(groupName);
        group->InitFromPrototype();
        group->GetComponent<TransformComponent>()->setPosition(leftShift, currentDeltaShiftY);
        currentDeltaShiftY += group->GetComponent<BoxCollisionComponent>()->GetCollisionBox().height * group->GetComponent<BoxCollisionComponent>()->getScale().y + deltaShiftY;
        itemTypes.push_back(group);
    }

    // items

    ChangeActiveItems();

    // bin

    Entity* bin = EntityManager::GetInstance().CreateEntity();
    bin->InitPrototype("bin");
    bin->InitFromPrototype();
    bin->GetComponent<TransformComponent>()->setPosition(710, 510);

    // Operations and Sockets

    ChangeSockets();

    // text

    text.setFont(*AssetManager::GetInstance().GetFont());
    text.setCharacterSize(25);

    text.setPosition(300, 20);
    text.setFillColor(sf::Color::White);
    text.setString("You nothing create yet!");
    text.setStyle(sf::Text::Bold);
}

void UIManager::ChangeVisibleItemTypes(EntityTypes newType)
{
    activeType = newType;
    ChangeActiveItems();
}

void UIManager::UpItemList()
{
    if (RecipeManager::GetInstance().GetKnownItems()[activeType].size() >= maxItemsCount)
    {
        ++currentItemStart;
        RecreateItems();
    }
}

void UIManager::DownItemList()
{
    if (RecipeManager::GetInstance().GetKnownItems()[activeType].size() >= maxItemsCount)
    {
        --currentItemStart;
        RecreateItems();
    }
}

void UIManager::NextOperation()
{
    switch (RecipeManager::GetInstance().currentDiscreteOperation)
    {
        case DiscreteOperations::Intersection:
        {
            RecipeManager::GetInstance().currentDiscreteOperation = DiscreteOperations::Union;
            break;
        }
        case DiscreteOperations::Union:
        {
            RecipeManager::GetInstance().currentDiscreteOperation = DiscreteOperations::Complement;
            break;
        }
        case DiscreteOperations::Complement:
        {
            RecipeManager::GetInstance().currentDiscreteOperation = DiscreteOperations::SymmetricDifference;
            break;
        }
        case DiscreteOperations::SymmetricDifference:
        {
            RecipeManager::GetInstance().currentDiscreteOperation = DiscreteOperations::AbsoluteComplement;
            break;
        }
        case DiscreteOperations::AbsoluteComplement:
        {
            RecipeManager::GetInstance().currentDiscreteOperation = DiscreteOperations::Intersection;
            break;
        }
        case DiscreteOperations::None:
        default:
        {
            __debugbreak();
        }
    };
    ChangeSockets();
}

sf::Text UIManager::GetUIText()
{
    sf::Text scaledText = text;
    scaledText.setPosition(300 * GameManager::GetInstance().GetTotalScale().x + GameManager::GetInstance().GetTotalShift().x, 20 * GameManager::GetInstance().GetTotalScale().y);
    scaledText.setCharacterSize(std::floor(25 * GameManager::GetInstance().GetTotalScale().x));
    return scaledText;
}

void UIManager::SetTextLastCreation(std::string inText)
{
    text.setString("Last you create - " + inText);
}

void UIManager::ChangeActiveItems()
{
    currentItemStart = 0;
    RecreateItems();
}

void UIManager::ChangeSockets()
{
    if (!discreteButton)
    {
        discreteButton = EntityManager::GetInstance().CreateEntity();
        discreteButton->InitPrototype("union");
        discreteButton->InitFromPrototype();
        discreteButton->GetComponent<TransformComponent>()->setPosition(455.f * GameManager::GetInstance().GetTotalScale().x + GameManager::GetInstance().GetTotalShift().x
            , 200.f * GameManager::GetInstance().GetTotalScale().y);
    }

    // sockets

    if (!RightSocket)
    {
        RightSocket = EntityManager::GetInstance().CreateEntity();
        RightSocket->InitPrototype("socket");
        RightSocket->InitFromPrototype();
        RightSocket->GetComponent<TransformComponent>()->setPosition(640 * GameManager::GetInstance().GetTotalScale().x + GameManager::GetInstance().GetTotalShift().x
            , 220 * GameManager::GetInstance().GetTotalScale().y);
    }

    if (!LeftSocket && RecipeManager::GetInstance().currentDiscreteOperation != DiscreteOperations::AbsoluteComplement)
    {
        LeftSocket = EntityManager::GetInstance().CreateEntity();
        LeftSocket->InitPrototype("socket");
        LeftSocket->InitFromPrototype();
        LeftSocket->GetComponent<TransformComponent>()->setPosition(300 * GameManager::GetInstance().GetTotalScale().x + GameManager::GetInstance().GetTotalShift().x
            , 220 * GameManager::GetInstance().GetTotalScale().y);
    }





    switch (RecipeManager::GetInstance().currentDiscreteOperation)
    {
        case DiscreteOperations::Intersection:
        {
            discreteButton->GetComponent<DrawableComponent>()->InitPrototype("intersection");
            discreteButton->GetComponent<DrawableComponent>()->InitFromPrototype();
            discreteButton->GetComponent<DrawableComponent>()->scale(GameManager::GetInstance().GetTotalScale());
            break;
        }
        case DiscreteOperations::Union:
        {
            discreteButton->GetComponent<DrawableComponent>()->InitPrototype("union");
            discreteButton->GetComponent<DrawableComponent>()->InitFromPrototype();
            discreteButton->GetComponent<DrawableComponent>()->scale(GameManager::GetInstance().GetTotalScale());
            break;
        }
        case DiscreteOperations::Complement:
        {
            discreteButton->GetComponent<DrawableComponent>()->InitPrototype("complement");
            discreteButton->GetComponent<DrawableComponent>()->InitFromPrototype();
            discreteButton->GetComponent<DrawableComponent>()->scale(GameManager::GetInstance().GetTotalScale());
            break;
        }
        case DiscreteOperations::SymmetricDifference:
        {
            discreteButton->GetComponent<DrawableComponent>()->InitPrototype("symmetric_difference");
            discreteButton->GetComponent<DrawableComponent>()->InitFromPrototype();
            discreteButton->GetComponent<DrawableComponent>()->scale(GameManager::GetInstance().GetTotalScale());
            break;
        }
        case DiscreteOperations::AbsoluteComplement:
        {
            discreteButton->GetComponent<DrawableComponent>()->InitPrototype("absolute_complement");
            discreteButton->GetComponent<DrawableComponent>()->InitFromPrototype();
            discreteButton->GetComponent<DrawableComponent>()->scale(GameManager::GetInstance().GetTotalScale());

            if (LeftSocket)
            {
                GameManager::GetInstance().GetEventDispatcher().LeaveChannel(ChannelEvent::Type::All, LeftSocket->GetUID());
                EntityManager::GetInstance().RemoveEntityByUID(LeftSocket->GetUID());
                LeftSocket = nullptr;
            }

            break;
        }
        case DiscreteOperations::None:
        default:
        {
            __debugbreak();
        }
    };
}

void UIManager::RecreateItems()
{

    for (auto& entity : items)
    {
        if (entity)
        {
            GameManager::GetInstance().GetEventDispatcher().LeaveChannel(ChannelEvent::Type::All, entity->GetUID());
            EntityManager::GetInstance().RemoveEntityByUID(entity->GetUID());
        }
    }
    items.clear();

    std::vector<const EntityPrototype*> entityPrototypes = RecipeManager::GetInstance().GetKnownItems()[activeType];

    const auto leftShift = (100.f * GameManager::GetInstance().GetTotalScale().x) + GameManager::GetInstance().GetTotalShift().x;
    const auto deltaShiftY = 20.f * GameManager::GetInstance().GetTotalScale().y;
    auto currentDeltaShiftY = 60.f * GameManager::GetInstance().GetTotalScale().y;

    int i = currentItemStart;
    i = i % static_cast<int>(maxItemsCount);
    if (i < 0)
    {
        i += static_cast<int>(maxItemsCount);
    }
    for (size_t k = 0; k < maxItemsCount && k < entityPrototypes.size(); ++k, ++i)
    {
        if (i == entityPrototypes.size())
        {
            i = 0;
        }
        Entity* Item = EntityManager::GetInstance().CreateEntity();
        Item->InitPrototype(entityPrototypes[i]->GetSID());
        Item->InitFromPrototype();
        Item->GetComponent<TransformComponent>()->setPosition(leftShift, currentDeltaShiftY);
        currentDeltaShiftY += Item->GetComponent<BoxCollisionComponent>()->GetCollisionBox().height * Item->GetComponent<BoxCollisionComponent>()->getScale().y + deltaShiftY;
        items.push_back(Item);
    }
}
