#pragma once

#include <Core/Singletons/BaseSingleton.h>
#include <Core/Prototypes/BasePrototype.h>
#include <Core/Consts/Enums.h>
#include <Core/CoreDefs.h>

#include <vector>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class Entity;
class EntityPrototype;

class CORE_API UIManager : public BaseSingleton<UIManager>
{
public:
    void Init() override;
    void ChangeVisibleItemTypes(EntityTypes newType);
    void UpItemList();
    void DownItemList();
    void NextOperation();
    const sf::Text& GetUIText();
    void SetTextLastCreation(std::string text);
    sf::Sprite GetBackground() const;
private:
    sf::Text text;
    sf::Sprite bg;
    std::vector<Entity*> itemTypes;
    std::vector<Entity*> items;
    Entity* discreteButton = nullptr;
    Entity* LeftSocket = nullptr;
    Entity* RightSocket = nullptr;
    //std::map<EntityTypes, std::vector<const EntityPrototype*>> allItems;
    EntityTypes activeType = EntityTypes::Basic;

    void ChangeActiveItems();
    void ChangeSockets();
    void RecreateItems();
    const size_t maxItemsCount = 4;
    int currentItemStart = 0;
};