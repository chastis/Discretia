#include <Core/Components/BaseComponent.h>

void BaseComponent::Init(Entity* inOwner)
{
    owner = inOwner;
}

void BaseComponent::Update(float deltaTime)
{

}
