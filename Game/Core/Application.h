#pragma once

#include <Core/EventSystem/EventCaller.h>
#include <Core/EventSystem/EventDispatcher.h>
#include <Core/Prototypes/ApplicationPrototype.h>
#include <Core/Interfaces/UIDInterface.h>
#include <Core/Utility/Noncopyable.h>
#include <Core/Utility/Nonmoveable.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>

class CORE_API Application : public Noncopyable, public Nonmoveable, public PrototypeableInterface<ApplicationPrototype>,  public EventCaller
{
    friend class ApplicationPrototype;
public:
    void InitFromPrototype() override;
    void InitEventFunctions() override;
    [[nodiscard]] bool IsRunning() const;
    void Run();
    void Update();
private:
    EventDispatcher eventDispatcher;
    sf::RenderWindow window;
};
