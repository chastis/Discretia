#pragma once

#include <Core/Singletons/BaseSingleton.h>
#include <Core/Prototypes/RecipePrototype.h>
#include <Core/Consts/Enums.h>
#include <Core/CoreDefs.h>
#include <vector>
#include <string>

class CORE_API RecipeManager : public BaseSingleton<RecipeManager>
{
public:
    void Init() override;
    const RecipePrototype* CheckExistRecipe(const std::vector<std::string>& elements, DiscreteOperations operation) const;
private:
};