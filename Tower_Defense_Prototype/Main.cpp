#include <SFML/Graphics.hpp>

#include "Tower.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	Tower testTower;
	testTower.setPosition(sf::Vector2f(640, 360));
	testTower.setAttackRange(200);
	testTower.setAttackSpeed(2);

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		testTower.update(window);

		window.clear();

		testTower.draw(window);

		window.display();
	}

	return 0;
}
