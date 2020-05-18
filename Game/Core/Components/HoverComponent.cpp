#include <Core/Components/HoverComponent.h>
#include <Core/Entity.h>

void HoverComponent::OnHoverBegin()
{
    hoverBegin(owner);
}

void HoverComponent::OnHoverEnd()
{
    hoverEnd(owner);
}