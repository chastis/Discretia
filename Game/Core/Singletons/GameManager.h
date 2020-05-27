#pragma once

#include <Core/EventSystem/EventDispatcher.h>
#include <Core/Singletons/BaseSingleton.h>
#include <Core/CoreDefs.h>
#include <SFML/Graphics.hpp>

class Application;

class CORE_API GameManager : public BaseSingleton<GameManager>
{
public:
    void InitFromApplication(Application* inApplication);
    [[nodiscard]] EventDispatcher& GetEventDispatcher() const;
    [[nodiscard]] const sf::RenderWindow& GetWindow() const;
    [[nodiscard]] sf::Vector2f GetTotalScale() const;
    [[nodiscard]] sf::Vector2f GetTotalShift() const;
private:
    void Init() override;
    Application* application = nullptr;
};