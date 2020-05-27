#include <Core/Singletons/RecipeManager.h>
#include <Core/Prototypes/EntityPrototype.h>

void RecipeManager::Init()
{
    AddKnownItem("ui_air");
    AddKnownItem("ui_water");
    AddKnownItem("ui_earth");
    AddKnownItem("ui_fire");
}

void RecipeManager::AddKnownItem(const std::string& SID)
{
    const auto& newPrototype = EntityPrototypes::Get(SID);
    allKnownItems[newPrototype.GetItemType()].push_back(&newPrototype);
}

bool RecipeManager::IsKnownItem(const std::string& SID)
{
    const auto& itemPrototype = EntityPrototypes::Get(SID);
    const auto KnownItemByTypes = allKnownItems[itemPrototype.GetItemType()];
    return std::find(KnownItemByTypes.begin(), KnownItemByTypes.end(), &itemPrototype) != KnownItemByTypes.end();
}

std::map<EntityTypes, std::vector<const EntityPrototype*>> RecipeManager::GetKnownItems() const
{
    return allKnownItems;
}

const RecipePrototype* RecipeManager::CheckExistRecipe(std::vector<std::string> elements, DiscreteOperations operation) const
{
    for (size_t i = 0; i < RecipePrototypes::Size(); ++i)
    {
        const RecipePrototype& currentRecipe =  RecipePrototypes::Get(i);
        if (currentRecipe.getOperation() == operation && elements.size() == currentRecipe.getElements().size())
        {
            auto elementsCopy = elements;
            bool recipeExist = true;
            std::vector<std::string> recipeElements = currentRecipe.getElements();
            auto el = elementsCopy.begin();
            while (el != elementsCopy.end())
            {
                auto findIt = std::find(recipeElements.begin(), recipeElements.end(), *el);
                if ( findIt == recipeElements.end())
                {
                    recipeExist = false;
                    break;
                }
                else
                {
                    recipeElements.erase(findIt);
                    elementsCopy.erase(el);
                    el = elementsCopy.begin();
                    if (el == elementsCopy.end())
                    {
                        break;
                    }
                }
            }
            if (recipeExist && recipeElements.empty() && elementsCopy.empty())
            {
                return &currentRecipe;
            }
        }
    }
    return nullptr;
}


