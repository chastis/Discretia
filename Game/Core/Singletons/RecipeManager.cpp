#include <Core/Singletons/RecipeManager.h>

void RecipeManager::Init()
{

}

const RecipePrototype* RecipeManager::CheckExistRecipe(const std::vector<std::string>& elements, DiscreteOperations operation) const
{
    for (size_t i = 0; i < RecipePrototypes::Size(); ++i)
    {
        const RecipePrototype& currentRecipe =  RecipePrototypes::Get(i);
        if (currentRecipe.getOperation() == operation && elements.size() == currentRecipe.getElements().size())
        {
            bool recipeExist = true;
            for (const auto& el : elements)
            {
                if (std::find(currentRecipe.getElements().begin(), currentRecipe.getElements().end(), el) == currentRecipe.getElements().end())
                {
                    recipeExist = false;
                    break;
                }
            }
            if (recipeExist)
            {
                return &currentRecipe;
            }
        }
    }
    return nullptr;
}


