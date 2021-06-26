#include <SFML/Graphics.hpp>

#include "tower.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    Tower testTower;

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