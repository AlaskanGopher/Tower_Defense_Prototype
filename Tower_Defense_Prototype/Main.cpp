#include <SFML/Graphics.hpp>

#include "tower.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");
    Tower testTower(1, 1, 100);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        testTower.draw(window);
        window.display();
    }

    return 0;
}