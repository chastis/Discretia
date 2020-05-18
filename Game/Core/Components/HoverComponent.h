#pragma once

#include <Core/Components/BaseComponent.h>
#include <Core/CoreDefs.h>
#include <functional>

class Entity;

class CORE_API HoverComponent : public BaseComponent
{
public:
    void OnHoverBegin();
    void OnHoverEnd();

    template <class Fn>
    void SetHoverBeginFunction(Fn&& hoverBeginFn)
    {
        hoverBegin = std::forward<Fn>(hoverBeginFn);
    }
    template <class Fn>
    void SetHoverEndFunction(Fn&& hoverEndFn)
    {
        hoverEnd = std::forward<Fn>(hoverEndFn);
    }
protected:
    std::function<void(Entity*)> hoverBegin;
    std::function<void(Entity*)> hoverEnd;
};