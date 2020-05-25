#include <Core/Factories/ComponentFactory.h>
#include <Core/Components/CollisionComponent.h>
#include <Core/Components/DrawableComponent.h>
#include <Core/Components/TransformComponent.h>

void ComponentFactory::Init()
{
    creatorComponents[typeid(BaseComponent)] = []() { return new BaseComponent(); };
    creatorComponents[typeid(BoxCollisionComponent)] = []() { return new BoxCollisionComponent(); };
    creatorComponents[typeid(DrawableComponent)] = []() { return new DrawableComponent(); };
    creatorComponents[typeid(TransformComponent)] = []() { return new TransformComponent(); };
}

BaseComponent* ComponentFactory::CreateComponent(TypeInfoRef type)
{
    const auto creatorComponentsIt = creatorComponents.find(type);
    if (creatorComponentsIt != creatorComponents.end())
    {
        return  creatorComponentsIt->second();
    }
    __debugbreak();
    return creatorComponents[typeid(BaseComponent)]();
}

BaseComponent* ComponentFactory::CreateComponent(const std::string& typeName)
{
    for (const auto& it : creatorComponents)
    {
        std::string itTypeName = std::string(it.first.get().name());
        if (itTypeName.find(typeName) != std::string::npos)
        {
            return it.second();
        }
    }
    __debugbreak();
    return creatorComponents[typeid(BaseComponent)]();
}
