#pragma once

#include <Core/Singletons/BaseSingleton.h>
#include <Core/Prototypes/RecipePrototype.h>
#include <Core/Consts/Enums.h>
#include <Core/CoreDefs.h>
#include <vector>
#include <string>

class EntityPrototype;

class CORE_API RecipeManager : public BaseSingleton<RecipeManager>
{
public:
    void Init() override;
    void AddKnownItem(const std::string& SID);
    bool IsKnownItem(const std::string& SID);
    [[nodiscard]] std::map<EntityTypes, std::vector<const EntityPrototype*>> GetKnownItems() const;
    [[nodiscard]] const RecipePrototype* CheckExistRecipe(std::vector<std::string> elements, DiscreteOperations operation) const;

    DiscreteOperations currentDiscreteOperation = DiscreteOperations::Union;
private:
    std::map<EntityTypes, std::vector<const EntityPrototype*>> allKnownItems;
};
