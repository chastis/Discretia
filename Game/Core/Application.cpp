#include <Core/Application.h>
#include <Core/Prototypes/ApplicationPrototype.h>
#include <Core/Singletons/PrototypeManager.h>
#include <Core/Singletons/AssetManager.h>
#include <Core/Singletons/EntityManager.h>
#include <Core/Components/DrawableComponent.h>
#include <Core/Entity.h>

bool Application::IsRunning() const
{
    return window.isOpen();
}
    
void Application::Init()
{
    PrototypeManager::CreateInstance();
    AssetManager::CreateInstance();
    EntityManager::CreateInstance();

    PrototypeManager::GetInstance().Init();
    AssetManager::GetInstance().Init();
    Entity* VPSHENEMY = EntityManager::GetInstance().CreateEntity();
    auto drawableComponent = VPSHENEMY->AddComponent<DrawableComponent>();
    drawableComponent->IniFromPrototype(SpritePrototypes::Get("vpsh"));

    const ApplicationPrototype& defaultPrototype = ApplicationPrototypes::GetDefault();
    window.create(sf::VideoMode(defaultPrototype.getWidth(), defaultPrototype.getHeight()), defaultPrototype.getTitle());
}

void Application::Update()
{
    sf::CircleShape shape;
    shape.setRadius(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.clear();
    for (const auto& entity : EntityManager::GetInstance().GetEntities())
    {
        auto drawableComponent = entity.second->GetComponent<DrawableComponent>();
        if (drawableComponent)
        {
            //drawableComponent.
            window.draw(*drawableComponent);
        }
    }
    
    window.display();
}
