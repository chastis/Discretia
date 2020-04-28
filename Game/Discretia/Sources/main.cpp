#include <Core/Singletons/EntityManager.h>
#include <Core/Utility/Ref/IntrusivePtr.h>
#include <SFML/Graphics.hpp>

struct Scene : ReferenceCountable<>
{
    sf::RenderWindow window;
    sf::CircleShape shape;
};

int main()
{
	EntityManager::Instance.CreateEntity();
    IntrusivePtr scene = MakeIntrusive<Scene>();
    scene->window.create(sf::VideoMode(200, 200), "Discretia");
    scene->shape.setRadius(100.f);
    scene->shape.setFillColor(sf::Color::Green);

    while (scene->window.isOpen())
    {
        sf::Event event;
        while (scene->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                scene->window.close();
        }

        scene->window.clear();
        scene->window.draw(scene->shape);
        scene->window.display();
    }

    return 0;
}